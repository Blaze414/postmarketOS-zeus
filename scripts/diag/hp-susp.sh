#!/bin/sh
PID=$(pgrep -o pulseaudio); U=$(stat -c %u /proc/$PID); S=unix:/run/user/$U/pulse/native
PA() { su -s /bin/sh $(getent passwd $U | cut -d: -f1) -c "XDG_RUNTIME_DIR=/run/user/$U pactl -s $S $*"; }
PA suspend-sink 0 1; PA suspend-source 1 1; sleep 3
N=$(wc -l < /home/pmos/diag.log); D=$(dmesg | wc -l)
true
timeout 8 speaker-test -D hw:0,0 -c2 -r48000 -F S16_LE -t sine -l1 > /tmp/st.out 2>&1
echo "speaker-test: $(grep -cE 'Front (Left|Right)' /tmp/st.out) channels played; $(grep -iE 'error|busy' /tmp/st.out | head -1)"
true
sleep 2
tail -n +$((N+1)) /home/pmos/diag.log > /tmp/all.log
echo "underrun=$(grep -c Underrun /tmp/all.log) nodata=$(grep -c 'actual data len 0' /tmp/all.log) bufdone=$(grep -c 0x5001004 /tmp/all.log) open_fail=$(grep -c 'Processing 0x01001000' /tmp/all.log)"
dmesg | tail -n +$((D+1)) | grep -E "ZEUSDBG|Failed|failed|Enable" | head -8
PA suspend-sink 0 0; PA suspend-source 1 0
echo SUSP_DONE
