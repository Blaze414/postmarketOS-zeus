#!/usr/bin/env bash
# Flash postmarketOS to a Xiaomi 12 Pro (zeus) over fastboot.
#
#   scripts/flash.sh              install - wipes userdata, asks first
#   scripts/flash.sh kernel       reflash boot only, keeping the install
#   scripts/flash.sh --yes ...    skip the confirmation prompt
#
# Run from the repo root on the machine holding ./out/pmb, with the phone in
# fastboot (power off, then hold Volume-Down + Power).
#
# Docker cannot pass USB through on macOS, so this runs on the host, not in the
# build container.
set -euo pipefail

OUT="${ZEUS_OUT:-out/pmb}"
ACTION="install"
ASSUME_YES=0

for a in "$@"; do
	case "$a" in
	kernel|install) ACTION="$a" ;;
	--yes|-y)       ASSUME_YES=1 ;;
	*) echo "unknown argument: $a" >&2; exit 2 ;;
	esac
done

die() { echo "!! $*" >&2; exit 1; }

command -v fastboot >/dev/null || die "fastboot not found (brew install android-platform-tools)"

# --- the device ---
dev=$(fastboot devices | awk 'NF {print $1; exit}')
[ -n "$dev" ] || die "no device in fastboot. Power off, then hold Volume-Down + Power."

unlocked=$(fastboot getvar unlocked 2>&1 | awk -F': ' '/^unlocked:/ {print $2; exit}')
case "$unlocked" in
yes) ;;
"")  echo "   (bootloader lock state not reported; continuing)" ;;
*)   die "bootloader is locked. Unlocking erases the phone and needs Xiaomi's
    approval and mi-unlock on Windows; there is no way around it." ;;
esac

slot=$(fastboot getvar current-slot 2>&1 | awk -F': ' '/^current-slot:/ {print $2; exit}')
[ -n "$slot" ] || slot="a"

echo "==> device $dev, current slot $slot"

need() { [ -f "$1" ] || die "missing $1 - run scripts/pmb.sh build first"; }

# --- what is about to happen ---
if [ "$ACTION" = "install" ]; then
	need "$OUT/vbmeta-disabled.img"
	need "$OUT/boot.img"
	need "$OUT/xiaomi-zeus-root.img"

	cat <<-MSG

	This installs postmarketOS and ERASES EVERYTHING on the phone -
	Android, your photos, your messages, all of it. There is no undo.

	  vbmeta_a, vbmeta_b   <- $OUT/vbmeta-disabled.img   (turns AVB off)
	  boot_$slot              <- $OUT/boot.img
	  userdata             <- $OUT/xiaomi-zeus-root.img  (the whole system)

	MSG
	if [ "$ASSUME_YES" -ne 1 ]; then
		printf "Type ERASE to continue: "
		read -r reply
		[ "$reply" = "ERASE" ] || die "not confirmed, nothing was written"
	fi

	# AVB first: this phone ships "Verity mode: true" and refuses an unsigned
	# kernel outright. Both slots, because the bootloader may fall back.
	echo "==> vbmeta (both slots)"
	fastboot --disable-verity --disable-verification flash vbmeta_a "$OUT/vbmeta-disabled.img"
	fastboot --disable-verity --disable-verification flash vbmeta_b "$OUT/vbmeta-disabled.img"

	echo "==> boot"
	fastboot flash boot "$OUT/boot.img"

	echo "==> userdata (this is the big one, a few minutes)"
	fastboot flash userdata "$OUT/xiaomi-zeus-root.img"
else
	need "$OUT/boot.img"
	echo
	echo "Reflashing the kernel only. userdata is left alone."
	echo

	# The boot.img pmbootstrap just built names the filesystem UUIDs of the
	# rootfs image built alongside it. Flashing it onto an install made from
	# an *earlier* build leaves the initramfs looking for a filesystem that
	# is not there, and the phone drops back to fastboot. Rewrite the
	# cmdline to name the UUIDs actually on the phone.
	img="$OUT/boot.img"
	if [ -n "${ZEUS_ROOT_UUID:-}" ]; then
		img="$OUT/boot-flash.img"
		python3 scripts/bootimg-uuid.py "$OUT/boot.img" "$img" \
			--root "$ZEUS_ROOT_UUID" \
			${ZEUS_BOOT_UUID:+--boot "$ZEUS_BOOT_UUID"}
	else
		echo "   (ZEUS_ROOT_UUID not set - flashing boot.img unchanged."
		echo "    Correct for a phone installed from this same build.)"
	fi

	if [ "$ASSUME_YES" -ne 1 ]; then
		printf "Flash %s to boot_%s? [y/N] " "$img" "$slot"
		read -r reply
		case "$reply" in y|Y|yes) ;; *) die "not confirmed" ;; esac
	fi
	fastboot flash boot "$img"
fi

echo "==> rebooting"
fastboot reboot

cat <<-MSG

	Done. First boot takes a couple of minutes while the filesystem is
	resized and the user is created.

	If it does not come up, hold Volume-Down + Power to get back to
	fastboot - that always works, and nothing here touches the bootloader.
MSG
