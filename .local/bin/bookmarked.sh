#!/bin/sh
xdotool type $(cat "${XDG_DATA_HOME:-$HOME/.local/share}/vault/bookmarks" | dmenu -i -l 10)
