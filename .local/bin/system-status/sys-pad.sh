#!/bin/sh
count=${1:-1}
char=${2:-' '}
printf -- "$char%.0s" $(seq 1 $count)
