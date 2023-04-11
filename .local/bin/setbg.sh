#!/bin/sh
bg_name="${XDG_DATA_HOME:-$HOME/.local/share}/bg"

is_temporary=$1
replace_name=${2:-$1}

if [ -n "$replace_name" ] && [ ! "$replace_name" = "-t" ]; then
  file_name=$(readlink -e "$replace_name")
  [ "$is_temporary" = "-t" ] \
    && mv "$file_name" "$bg_name" \
    || ln -sf "$file_name" "$bg_name"
fi

xwallpaper --zoom "$bg_name"
