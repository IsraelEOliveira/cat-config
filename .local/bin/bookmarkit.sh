#!/bin/sh
bookmarks="${XDG_DATA_HOME:-$HOME/.local/share}/vault/bookmarks"
content=$(xclip -o)

mkdir -p $(dirname "$bookmarks")
touch "$bookmarks"

if ! grep -qe "^$content$" "$bookmarks"; then
  echo "$content" >> "$bookmarks"
fi
