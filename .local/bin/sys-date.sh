#!/usr/bin/env sh
clock_set=(🕛 🕐 🕑 🕒 🕓 🕔 🕕 🕖 🕗 🕘 🕙 🕚 🕛)
icon=${clock_set[$(date '+%I')]}

date "+%Y %b %d (%a) $icon%I:%M%p"
