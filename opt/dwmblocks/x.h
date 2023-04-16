#ifndef STATUS_BLOCKS_X_H
#define STATUS_BLOCKS_X_H

#include <X11/Xlib.h>


int  get_display();
void write_root_window(char const *);
void close_display();

#endif // STATUS_BLOCKS_X_H
