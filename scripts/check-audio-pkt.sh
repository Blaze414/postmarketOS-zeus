#!/bin/bash
# Compile-check audio_pkt.c and patch 0016 against the kernel tree, without
# waiting on a full image build. Run inside the build container.
set -euo pipefail
K=/src/linux
P=/work/src/pmaports/linux-postmarketos-qcom-sm8450-zeus
cd "$K"

cleanup() {
	git checkout -- drivers/soc/qcom/apr.c drivers/soc/qcom/Makefile \
		drivers/soc/qcom/Kconfig include/linux/soc/qcom/apr.h 2>/dev/null || true
	rm -f drivers/soc/qcom/audio_pkt.c drivers/soc/qcom/audio_pkt.h
}
trap cleanup EXIT

cleanup
git apply -p1 "$P"/0016-soc-qcom-allow-registering-a-gpr-port-at-a-chosen-id.patch
git apply -p1 "$P"/0017-soc-qcom-apr-optional-gpr-packet-tracing.patch
cp /work/src/kernel/audio_pkt.c /work/src/kernel/audio_pkt.h drivers/soc/qcom/

grep -q CONFIG_QCOM_AUDIO_PKT .config || echo 'CONFIG_QCOM_AUDIO_PKT=y' >> .config
make -s ARCH=arm64 olddefconfig >/dev/null
grep -q '^CONFIG_QCOM_AUDIO_PKT=y' .config || { echo "!! symbol not enabled"; exit 1; }

make ARCH=arm64 -j"$(nproc)" drivers/soc/qcom/audio_pkt.o drivers/soc/qcom/apr.o
echo "=== OK: audio_pkt.o and apr.o built ==="
