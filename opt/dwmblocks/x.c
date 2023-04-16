#include "x.h"


static Display * dpy;
static int       screen;
static Window	 root;


void write_root_window(char const * status) {
	XStoreName(dpy, root, status);
	XFlush(dpy);
}

int get_display() {
	dpy = XOpenDisplay(NULL);
	
	if (dpy) {
		screen = DefaultScreen(dpy);
		root = RootWindow(dpy, screen);
		return 1;
	}
	
	return 0;
}

void close_display() {
	XCloseDisplay(dpy);
}
