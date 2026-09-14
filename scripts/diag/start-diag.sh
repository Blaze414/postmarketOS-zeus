#!/bin/sh
pkill diag-router; pkill -f diagcat.py; sleep 1
rm -f /home/pmos/diag.log
start-stop-daemon -S -b -m -p /run/diagcat.pid -x /usr/bin/python3 -- /home/pmos/diagcat.py /home/pmos/diag.log
sleep 2
start-stop-daemon -S -b -m -p /run/diag-router.pid -1 /home/pmos/router.out -2 /home/pmos/router.out -x /home/pmos/diag/diag-router -- -s 127.0.0.1:2500
sleep 12
chmod 644 /home/pmos/diag.log /home/pmos/router.out 2>/dev/null
echo STARTED
