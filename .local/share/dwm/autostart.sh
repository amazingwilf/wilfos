#!/usr/bin/env bash

export XDG_CURRENT_DESKTOP='dwm'

_ps=(pipewire ksuperkey)
for _prs in "${_ps[@]}"; do
	if [[ `pidof ${_prs}` ]]; then
		killall -9 ${_prs}
	fi
done

/usr/bin/pipewire &

if [[ ! `pidof polkit-gnome-authentication-agent-1` ]]; then
	/usr/libexec/polkit-gnome-authentication-agent-1 &
fi

ksuperkey -e 'Super_L=Alt_L|F1' &
ksuperkey -e 'Super_R=Alt_L|F1' &

xsetroot -cursor_name left_ptr

nitrogen --restore

killall -q picom
while pgrep -u $UID -x picom >/dev/null; do sleep 1; done
picom &
