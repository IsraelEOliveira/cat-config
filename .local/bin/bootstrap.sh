#!/bin/bash
name='sdm'
cmd="/usr/bin/git --git-dir=$HOME/.$name --work-tree=$HOME"

git init --bare "$HOME/.$name"
eval "$cmd config --local status.showUntrackedFiles no"
echo "alias sdm='$cmd'" >> $HOME/.bashrc
