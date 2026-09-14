#!/bin/sh
PID=$(pgrep -o pulseaudio); U=$(stat -c %u /proc/$PID); S=unix:/run/user/$U/pulse/native
PA() { su -s /bin/sh $(getent passwd $U | cut -d: -f1) -c "XDG_RUNTIME_DIR=/run/user/$U pactl -s $S $*"; }
nid() { amixer -c0 controls | grep "name='$1'" | sed -E 's/numid=([0-9]+).*/\1/'; }
TDM=$(nid 'Tertiary TDM0 Audio Mixer MultiMedia1'); HP=$(nid 'RX_CODEC_DMA_RX_0 Audio Mixer MultiMedia1')
echo "numids: tdm=$TDM hp=$HP mode=$1"
if [ "$1" = hp ]; then ON=$HP; OFF=$TDM; else ON=$TDM; OFF=$HP; fi
PA suspend-sink 0 1; PA suspend-source 1 1; sleep 3
N=$(wc -l < /home/pmos/diag.log)
amixer -c0 cset numid=$OFF 0 >/dev/null 2>&1; amixer -c0 cset numid=$ON 1 >/dev/null 2>&1
timeout 6 aplay -D hw:0,0 -t raw -f S16_LE -r 48000 -c 2 /dev/urandom > /tmp/st.out 2>&1
echo "aplay: $(head -3 /tmp/st.out | tr "\n" " ")"
amixer -c0 cset numid=$ON 0 >/dev/null 2>&1; amixer -c0 cset numid=$HP 1 >/dev/null 2>&1
sleep 2
tail -n +$((N+1)) /home/pmos/diag.log > /home/pmos/run-$1.log; chmod 644 /home/pmos/run-$1.log
L=/home/pmos/run-$1.log
echo "underrun=$(grep -c Underrun $L) nodata=$(grep -c 'actual data len 0' $L) bufdone=$(grep -c 0x5001004 $L) devmods=$(grep -oE 'MODULE:[0-9a-f]+|Module 0x[0-9a-f]+' $L | sort -u | tr '\n' ' ')"
PA suspend-sink 0 0; PA suspend-source 1 0
echo RUN_DONE
