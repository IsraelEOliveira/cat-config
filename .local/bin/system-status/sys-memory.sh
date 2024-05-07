#!/bin/sh

case $BUTTON in
	1) notify-send "Memory hogs" "$(ps axch -o cmd:15,%mem --sort=-%mem | head)" ;;
	2) "$TERMINAL" -e "$EDITOR" "$0" ;;
	3) setsid -f "$TERMINAL" -e top ;;
esac

free --mebi | sed -n '2{p;q}' | awk '{printf ("%2.2fGiB\n", ( $3 / 1024))}'
