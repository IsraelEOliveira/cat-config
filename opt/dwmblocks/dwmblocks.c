#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include "x.h"


#define SIGPLUS				SIGRTMIN
#define SIGMINUS			SIGRTMIN
#define CMDLENGTH			50
#define LENGTH(X)			(sizeof(X) / sizeof (X[0]))
#define MIN(a, b)			((a < b) ? a : b)
#define STATUSLENGTH	(LENGTH(blocks) * CMDLENGTH + 1)


typedef struct {
	char const * icon;
	char const * command;
	unsigned int interval;
	unsigned int signal;
} Block;

#include "blocks.h"

void	scan_blocks_interval(int);
void	scan_blocks_hook(unsigned int);

void	register_hooks();
void	handle_hook(int, siginfo_t *, void *);
void	handle_hook_contextless(int);
void	handle_terminate();
void	handle_noop(int);

void	event_loop();
int		assemble_status(char *, char *);

void	write_status();
void	write_stdout(char const *);
static void	(*write_method)(char const *) = write_root_window;

static char blocks_buffer[LENGTH(blocks)][CMDLENGTH] = {0};
static char status_buffer[2][STATUSLENGTH];
static char action[] = "\0";
static int	terminate_absent = 1;


FILE * invoke(char const * command) {
	FILE * process_file;

	if (*action) {
		setenv("BUTTON", action, 1);
		process_file = popen(command, "r");
		*action = '\0';
		unsetenv("BUTTON");
	}
	else {
		process_file = popen(command, "r");
	}

	return process_file;
}

void run_block(Block const * block, char * output) {
	if (block->signal) {
		output[0] = block->signal;
		output++;
	}

	strcpy(output, block->icon);
	FILE * trunk = invoke(block->command);

	if (trunk) {
		int i = strlen(block->icon);
		fgets(output + i, CMDLENGTH - i - delimLen, trunk);
		i = strlen(output);

		if (i) {
			i = output[i - 1] == '\n' ? i - 1 : i;
			if (delim[0] != '\0') {
				strncpy(output + i, delim, delimLen); 
			}
			else {
				output[i++] = '\0';
			}
		}

		pclose(trunk);
	}
}

void scan_blocks_interval(int interval) {
	for (unsigned int i = 0; i < LENGTH(blocks); ++i) {
		Block const * current = blocks + i;
		if ((current->interval != 0 && interval % current->interval == 0) || interval == -1) {
			run_block(current, blocks_buffer[i]);
		}
	}
}

void scan_blocks_hook(unsigned int id) {
	for (unsigned int i = 0; i < LENGTH(blocks); ++i) {
		Block const * current = blocks + i;
		if (current->signal == id) {
			run_block(current, blocks_buffer[i]);
		}
	}
}

void register_hooks() {
	for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
		signal(i, handle_noop);
	}
	
	struct sigaction sa = { .sa_sigaction = handle_hook, .sa_flags = SA_SIGINFO };
	sigaction(SIGUSR1, &sa, NULL);

	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		if (blocks[i].signal > 0) {
			signal(SIGMINUS + blocks[i].signal, handle_hook_contextless);
		}
	}
}

int assemble_status(char * str, char * last) {
	strcpy(last, str);
	str[0] = '\0';
	
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		strcat(str, blocks_buffer[i]);
	}
	
	str[strlen(str) - strlen(delim)] = '\0';
	
	return strcmp(str, last);
}

void write_status() {
	if (assemble_status(status_buffer[0], status_buffer[1])) {
		write_method(status_buffer[0]);
	}
}

void write_stdout(char const * status) {
	printf("%s\n", status);
	fflush(stdout);
}

void event_loop() {
	register_hooks();

	for (int i = -1; terminate_absent; ++i) {
		scan_blocks_interval(i);
		write_status();

		sleep(1.0f);
	}
}

void handle_hook(int id, siginfo_t * si, void *) {
	if (si) {
		*action = ('0' + si->si_value.sival_int) & 0xff;
		id = si->si_value.sival_int >> 8;
	}

	scan_blocks_hook(id);
	write_status();
}

void handle_hook_contextless(int sig) {
	handle_hook(sig, NULL, NULL);
}

void handle_terminate() {
	terminate_absent = 0;
}

void handle_noop(int) {
}

int main(int argc, char ** argv) {
	for (int i = 0; i < argc; i++) {
		if (strcmp("-d", argv[i]) == 0) {
			strncpy(delim, argv[++i], delimLen);
		}
		else if (strcmp("-p", argv[i]) == 0) {
			write_method = write_stdout;
		}
	}
	
	if (get_display()) {
		delimLen = MIN(delimLen, strlen(delim));
		delim[delimLen++] = '\0';
	
		signal(SIGTERM, handle_terminate);
		signal(SIGINT, handle_terminate);
	
		event_loop();
	
		close_display();
		
		return 0;
	}
	else {
		fprintf(stderr, "dwmblocks: Failed to open display\n");
	}
	
	return 1;
}
