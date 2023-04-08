/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar        = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
static const int user_bh = 7;               /* add an defined amount of pixels to the bar height */

/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"iosevka:Mono:size=10"
};

static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */

static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#bbbbbb", "#222222" },
	[SchemeSel]  = { "#eeeeee", "#0c0c0c" },
	[SchemeOut]  = { "#000000", "#0c0c0c" },
};

/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
