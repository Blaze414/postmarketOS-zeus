#!/bin/bash
# Check that the built rootfs carries every fix this port has accumulated, so a
# fresh install has them out of the box rather than only the phone we happen to
# have been iterating on.
#
# Run inside the build container (scripts/dev.sh), after scripts/pmb.sh build.
set -uo pipefail

R=/src/pmb-work/chroot_rootfs_xiaomi-zeus
pass=0; fail=0

ok()   { printf '  \033[32mok\033[0m    %s\n' "$1"; pass=$((pass+1)); }
bad()  { printf '  \033[31mMISS\033[0m  %s\n' "$1"; fail=$((fail+1)); }

have() { # have <description> <path>
	# -e follows the link, and a chroot's absolute symlinks resolve against
	# the host from out here, so accept a symlink whose target exists inside
	# the chroot too.
	if sudo test -e "$R$2"; then
		ok "$1"
	elif sudo test -L "$R$2" &&
	     sudo test -e "$R$(sudo readlink "$R$2")"; then
		ok "$1"
	else
		bad "$1 ($2)"
	fi
}
grep_in() { # grep_in <description> <path> <pattern>
	if sudo grep -q "$3" "$R$2" 2>/dev/null; then ok "$1"; else bad "$1 ($2)"; fi
}

echo "== packages installed =="
for p in linux-postmarketos-qcom-sm8450-zeus device-xiaomi-zeus \
	 firmware-xiaomi-zeus-adsp firmware-xiaomi-zeus-gpu \
	 firmware-xiaomi-zeus-modem qbootctl-openrc postmarketos-ui-phosh; do
	v=$(sudo grep -A1 "^P:$p$" "$R"/lib/apk/db/installed 2>/dev/null | sed -n 's/^V://p')
	if [ -n "$v" ]; then ok "$p $v"; else bad "$p not installed"; fi
done

echo
echo "== CPU: turbo unlock, conservative by default =="
have "boot hook"            /etc/local.d/zeus-cpufreq.start
have "profile switcher"     /usr/bin/zeus-cpu-profile
grep_in "boot uses the switcher" /etc/local.d/zeus-cpufreq.start "zeus-cpu-profile"
grep_in "conservative caps prime at 1728000" /usr/bin/zeus-cpu-profile "1728000"
grep_in "boost dropped before caps are written" /usr/bin/zeus-cpu-profile "boost"

echo
echo "== WiFi: WCN6855 PCIe ASPM + power save =="
have "ASPM boot hook"       /etc/local.d/zeus-wifi.start
grep_in "sets ASPM policy to performance" /etc/local.d/zeus-wifi.start "performance"
have "NetworkManager drop-in" /etc/NetworkManager/conf.d/wifi-powersave-off.conf
grep_in "powersave disabled"  /etc/NetworkManager/conf.d/wifi-powersave-off.conf "wifi.powersave = 2"

echo
echo "== audio =="
have "ALSA UCM profile"     /usr/share/alsa/ucm2/conf.d/sm8450/Xiaomi-12.conf
have "ALSA UCM HiFi"        /usr/share/alsa/ucm2/Qualcomm/sm8450/Zeus/HiFi.conf
have "ADSP topology symlink" /lib/firmware/qcom/sm8450/Xiaomi-12-tplg.bin.zst

echo
echo "== display and shell =="
have "phoc config"          /etc/phosh/phoc.ini
have "panel cutout"         /usr/share/gmobile/devices/display-panels/xiaomi,zeus.json
have "phosh session wrapper" /usr/bin/zeus-phosh-session
have "on-screen keyboard autostart" /etc/xdg/autostart/sm.puri.OSK0.desktop

echo
echo "== A/B slot =="
have "qbootctl in default runlevel" /etc/runlevels/default/qbootctl

echo
echo "== kernel modules and environment =="
have "modules-load"         /etc/modules-load.d/zeus.conf
have "environment hook"     /etc/local.d/zeus-environment.start

echo
echo "== firmware =="
have "ADSP firmware"        /lib/firmware/qcom/sm8450/zeus
have "GPU firmware"         /lib/firmware/qcom/a730_sqe.fw.zst

echo "== kernel =="
BOOT=/work/out/pmb/boot.img
DTB=/work/out/pmb/sm8450-xiaomi-zeus.dtb
if [ -f "$BOOT" ]; then
	v=$(python3 - "$BOOT" <<-'PY'
	import re, sys, zlib
	d = open(sys.argv[1], "rb").read()
	i = d.find(b"\x1f\x8b\x08")
	k = zlib.decompressobj(31).decompress(d[i:])
	m = re.search(rb"Linux version [^\x00]{0,200}", k)
	print(m.group(0).decode().split(") ")[-1].split(" SMP")[0] if m else "?")
	PY
	)
	ok "boot.img kernel $v"
else
	bad "boot.img missing"
fi
if [ -f "$DTB" ]; then
	# Decompile once. Piping dtc into `grep -q` makes grep close the pipe
	# early, and with pipefail that reads as a failed check.
	dts=$(mktemp)
	dtc -I dtb -O dts "$DTB" > "$dts" 2>/dev/null
	check_dt() { # check_dt <description> <pattern>
		if grep -q "$2" "$dts"; then ok "devicetree: $1"; else bad "devicetree: $1"; fi
	}
	check_dt "zeus board"            "xiaomi,zeus"
	check_dt "GPR passthrough node"  "qcom,audio-pkt\""
	check_dt "DSP buffer node"       "qcom,audio-pkt-mem"
	check_dt "speaker TDM pins"      "mi2s2_sck"
	check_dt "panel"                 "l2-38-0c-0a-dsc"
	rm -f "$dts"
else
	bad "dtb missing"
fi

echo
printf '\n%d ok, %d missing\n' "$pass" "$fail"
[ "$fail" -eq 0 ] || exit 1
