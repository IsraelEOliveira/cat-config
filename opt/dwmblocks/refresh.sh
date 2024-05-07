#!/usr/bin/env sh
make
if [ $? = 0 ]; then
	sudo make install clean
	pkill dwmblocks
	setsid dwmblocks >/dev/null 2>&1 &
fi
