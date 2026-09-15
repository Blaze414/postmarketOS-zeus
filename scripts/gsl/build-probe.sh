#!/bin/sh
# Probe how much of AudioReach graphservices (GSL/GPR/ACDB/ar_osal) compiles for
# postmarketOS (Alpine, musl, aarch64). See docs/12-audioreach-userspace-port.md.
#
# Run inside the pmbootstrap native chroot with the graphservices tree at
# /home/pmos/gsbuild/gs:
#   git clone --depth 1 https://github.com/AudioReach/audioreach-graphservices gs
#   pmbootstrap chroot -- apk add build-base
#   pmbootstrap chroot -- sh /home/pmos/gsbuild2.sh
cd /home/pmos/gsbuild/gs; rm -f *.o
INC=""
# every dir that contains headers, plus the generic ar_utils variant (not hexagon/audioss)
for d in $(find gpr acdb ar_osal ar_util gsl spf public_headers -type d 2>/dev/null | grep -vE "ar_utils/(hexagon|audioss)"); do
  ls "$d"/*.h >/dev/null 2>&1 && INC="$INC -I$d"
done
FLAGS="-w -fPIC -D__unused= -D_GNU_SOURCE"
echo "include dirs: $(echo $INC | wc -w)"
build() {
  name="$1"; shift
  n=0; ok=0
  for f in "$@"; do
    n=$((n+1))
    gcc -c $FLAGS $INC "$f" -o "/tmp/o_$(basename $f .c).o" 2>/tmp/err_$$ && ok=$((ok+1)) || { [ $ok -lt 0 ] || true; head -1 /tmp/err_$$ >> /tmp/fails_$name; }
  done
  echo "$name: $ok/$n compiled"
  [ -f /tmp/fails_$name ] && { echo "  first failures:"; sort -u /tmp/fails_$name | head -4; }
}
rm -f /tmp/fails_*
build ar_osal $(ls ar_osal/src/linux/ar_osal_*.c | grep -v ar_osal_log.c | grep -v ar_osal_shmem_phy.c | grep -v ar_osal_signal2.c)
build gpr $(ls gpr/core/src/hash_based/*.c gpr/datalinks/gpr_lx/src/gpr_lx.c 2>/dev/null)
build gsl $(ls gsl/src/*.c 2>/dev/null)
build acdb $(ls acdb/src/*.c 2>/dev/null)
