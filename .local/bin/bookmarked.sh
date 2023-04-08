#!/bin/sh
xdotool type $(cat "$HOME/.local/share/sickle/bookmarks" | dmenu -i -l 10)
