#!/bin/sh
PID=$(pgrep -o pulseaudio); U=$(stat -c %u /proc/$PID); S=unix:/run/user/$U/pulse/native
PA() { su -s /bin/sh $(getent passwd $U | cut -d: -f1) -c "XDG_RUNTIME_DIR=/run/user/$U pactl -s $S $*"; }
mount -t debugfs none /sys/kernel/debug 2>/dev/null
PA suspend-sink 0 1; PA suspend-source 1 1; sleep 3
amixer -c0 cset numid=254 0 >/dev/null 2>&1; amixer -c0 cset numid=250 1 >/dev/null 2>&1
timeout 8 speaker-test -D hw:0,0 -c2 -r48000 -F S16_LE -t sine -l1 >/dev/null 2>&1 &
sleep 3
C=/sys/kernel/debug/clk/LPASS_CLK_ID_TER_TDM_IBIT
echo "during play: enable=$(cat $C/clk_enable_count) prepare=$(cat $C/clk_prepare_count) rate=$(cat $C/clk_rate)"
grep -l . /sys/kernel/debug/clk/*/clk_enable_count 2>/dev/null | while read f; do v=$(cat $f); [ "$v" != 0 ] && echo "  on: $(basename $(dirname $f))=$v"; done | grep -i lpass
wait
amixer -c0 cset numid=250 0 >/dev/null 2>&1; amixer -c0 cset numid=254 1 >/dev/null 2>&1
PA suspend-sink 0 0; PA suspend-source 1 0
dmesg | grep -iE "bclk|q6prm|prm" | tail -5
echo LIVE_DONE
