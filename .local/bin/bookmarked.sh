#!/bin/sh
xdotool type $(cat "${XDG_DATA_HOME:-$HOME/.local/share}/sickle/bookmarks" | dmenu -i -l 10)
