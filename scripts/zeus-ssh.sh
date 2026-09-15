#!/usr/bin/env bash
# Run a command on the device over USB networking, or install this Mac's key.
#
#   scripts/zeus-ssh.sh setup          - push ~/.ssh/id_ed25519.pub, once
#   scripts/zeus-ssh.sh <command...>   - run it; key auth once setup has run
#   scripts/zeus-ssh.sh push src dst   - copy a file over
#
# Before the key is installed this falls back to the throwaway password from
# pmb.sh (ZEUS_PASSWORD, default 147147), fed through SSH_ASKPASS - ssh will
# not read a password from a pipe, but it will run an askpass helper.
set -uo pipefail

HOST="${ZEUS_HOST:-172.16.42.1}"
USER_="${ZEUS_USER:-pmos}"
PASS="${ZEUS_PASSWORD:-147147}"
SSHOPT=(-o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null
	-o LogLevel=ERROR -o ConnectTimeout=10)

setup_askpass() {
	ASKPASS=$(mktemp)
	printf '#!/bin/sh\nprintf %%s %s\n' "$PASS" > "$ASKPASS"
	chmod 700 "$ASKPASS"
	export SSH_ASKPASS="$ASKPASS" SSH_ASKPASS_REQUIRE=force DISPLAY=:0
	trap 'rm -f "$ASKPASS"' EXIT
}

case "${1:-}" in
setup)
	setup_askpass
	ssh "${SSHOPT[@]}" -o PubkeyAuthentication=no "$USER_@$HOST" \
		'mkdir -p ~/.ssh && chmod 700 ~/.ssh && cat >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys && sort -u -o ~/.ssh/authorized_keys ~/.ssh/authorized_keys' \
		< ~/.ssh/id_ed25519.pub && echo "key installed"
	;;
push)
	shift
	scp "${SSHOPT[@]}" "$@"
	;;
*)
	exec ssh "${SSHOPT[@]}" "$USER_@$HOST" "$@"
	;;
esac
