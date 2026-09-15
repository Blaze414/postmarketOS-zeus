#!/bin/sh
# Build gslprobe and gprprobe for the device (Alpine, musl, aarch64).
# Run inside the privileged build container:
#   docker ... zeus-build sh /work/scripts/gsl/build.sh
#
# The pmbootstrap native chroot is already an aarch64 Alpine with a working
# toolchain, which is exactly the target userland - no cross setup needed.
set -eu

CFG=/src/pmbootstrap.cfg
APORTS=/src/pmaports-zeus
WORK=/src/pmb-work
PMB="pmbootstrap -c $CFG -p $APORTS -w $WORK"
CHROOT="$WORK/chroot_native"
GS_SRC=/work/out/gsl-port/gs

$PMB -y chroot -- apk add -q build-base

# The chroot cannot see /work, so stage the sources inside it.
sudo rm -rf "$CHROOT/home/pmos/gslbuild"
sudo mkdir -p "$CHROOT/home/pmos/gslbuild"
sudo cp -r "$GS_SRC" "$CHROOT/home/pmos/gslbuild/gs"
sudo cp /work/scripts/gsl/Makefile /work/scripts/gsl/gslprobe.c \
	/work/scripts/gsl/stubs.c /work/scripts/gsl/gprprobe.c /work/scripts/gsl/ar_compat.h \
	"$CHROOT/home/pmos/gslbuild/"
sudo chown -R 12345:12345 "$CHROOT/home/pmos/gslbuild" 2>/dev/null || true

$PMB -y chroot -- sh -c 'cd /home/pmos/gslbuild && \
	make GS=/home/pmos/gslbuild/gs && \
	gcc -O2 -Wall -o gprprobe gprprobe.c'

sudo cp "$CHROOT/home/pmos/gslbuild/gslprobe" "$CHROOT/home/pmos/gslbuild/gprprobe" /work/out/
sudo chown "$(id -u):$(id -g)" /work/out/gslprobe /work/out/gprprobe
file /work/out/gslprobe /work/out/gprprobe
