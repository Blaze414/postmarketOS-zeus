#!/usr/bin/env bash
# Run one command on the device as root.
#
#   scripts/zeus-sudo.sh 'dmesg | tail -40'
#
# doas insists on a tty and will not take a password on stdin, so this drives
# an interactive ssh with expect. Key auth still does the login; the password
# here (ZEUS_PASSWORD) is only for doas itself.
set -uo pipefail

HOST="${ZEUS_HOST:-172.16.42.1}"
USER_="${ZEUS_USER:-pmos}"
PASS="${ZEUS_PASSWORD:-147147}"
CMD="$*"

# base64 so neither Tcl nor the remote shell can reinterpret quoting in it.
export ZPASS="$PASS" ZDEST="$USER_@$HOST"
ZCMD="echo $(printf %s "$CMD" | base64 | tr -d '\n') | base64 -d | sudo sh"
export ZCMD

# Passed through the environment, not argv: `expect -c` treats trailing
# arguments as script files rather than filling in $argv.
exec expect -c '
	set timeout 300
	set pass $env(ZPASS)
	set dest $env(ZDEST)
	set cmd  $env(ZCMD)
	log_user 1
	spawn -noecho ssh -tt -o StrictHostKeyChecking=no \
		-o UserKnownHostsFile=/dev/null -o LogLevel=ERROR \
		$dest $cmd
	expect {
		-re {[Pp]assword:} { send "$pass\r"; exp_continue }
		eof
	}
	catch wait result
	exit [lindex $result 3]
'
