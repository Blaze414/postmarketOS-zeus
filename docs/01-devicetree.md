# 01 — Deriving sm8450-xiaomi-zeus.dts

The whole port hinges on this file. Everything else is packaging.

## The method

You have two descriptions of the same hardware:

1. `stock-dump/zeus-stock.dts` — Xiaomi's downstream description. Complete and correct,
   but written against Qualcomm's out-of-tree 5.10 kernel. Wrong bindings, wrong node names,
   full of vendor properties mainline has never heard of. **Reference, not source.**
2. `sm8450-xiaomi-cupid.dts` — mainline, correct bindings, wrong device. **Template.**

The job: walk cupid's 1283 lines, and for each node ask "is zeus's version of this the
same part?" If yes, keep. If no, find the real part in the stock dts and re-express it
in mainline bindings.

```bash
# start from the sibling
cp linux/arch/arm64/boot/dts/qcom/sm8450-xiaomi-cupid.dts \
   linux/arch/arm64/boot/dts/qcom/sm8450-xiaomi-zeus.dts
```

Register it in the build:

```bash
# in arch/arm64/boot/dts/qcom/Makefile, next to the cupid line
dtb-$(CONFIG_ARCH_QCOM) += sm8450-xiaomi-zeus.dtb
```

## What to keep from cupid (same silicon, don't touch)

CPU/cache topology, SMMU, interconnects, UFS, USB, PMIC (PM8350-family), regulators,
RPMh, cpufreq, thermal zones, WiFi/BT (WCN6855), Adreno 730 GPU node.

These are SoC- and reference-design-level. cupid and zeus share them.

## What you must change

Work these in order — each is independently testable.

### a) Board identity

```dts
/ {
	model = "Xiaomi 12 Pro";
	compatible = "xiaomi,zeus", "qcom,sm8450";
};
```

### b) Display panel — the big one

zeus: 1440x3200, LTPO, curved, Samsung AMOLED, 120Hz, DSC 1.1.
cupid: 1080x2400, flat, 120Hz.

Different panel = different `compatible`, different init sequence, different DSI timings,
different DSC slice config. Find the truth in the stock dts:

```bash
# locate the panel node and its timings in Xiaomi's own description
grep -n -A80 'panel\|dsi_panel\|qcom,mdss-dsi' stock-dump/zeus-stock.dts | less
# the init command stream is usually qcom,mdss-dsi-on-command as a hex blob
```

You will likely need to **write a new panel driver** under
`drivers/gpu/drm/panel/` unless zeus's panel already has one. Check first:

```bash
grep -ril "samsung" linux/drivers/gpu/drm/panel/ | xargs grep -l "sm8450\|1440x3200" 2>/dev/null
```

`linux-mdss-dsi-panel-driver-generator` (msm8916-mainline tooling) converts a downstream
`qcom,mdss-dsi-*` panel node directly into a mainline panel driver skeleton. Use it — do
not hand-transcribe the init command hex.

### c) Touchscreen

Find the part on the I2C/SPI bus in the stock dts, check for a mainline driver, wire it up.
Common on this era: Focaltech, Goodix, Novatek. Novatek has the weakest mainline story.

### d) Regulators feeding panel/touch

Panel supplies differ between the two boards. Mismatched regulator = black screen that
looks exactly like a broken panel driver. Cross-check against the stock dts before blaming
the panel.

### e) Partition offsets

zeus and cupid have different `super` layouts. Read them from `stock-dump/inventory.txt`
and fix `deviceinfo_super_partitions` in the device package.

## Verification per stage

Do not batch these. One change, one boot, one check.

| Stage | Check |
|---|---|
| dts compiles | `make sm8450-xiaomi-zeus.dtb` clean |
| kernel boots at all | pmOS boots to a shell over USB networking (ssh 172.16.42.1) — even with a black screen |
| panel | backlight on, console visible |
| touch | `evtest` reports events |
| GPU | `glxinfo`/`eglinfo` shows freedreno, not llvmpipe |

**Boot-to-SSH-with-black-screen is the real first milestone.** If you chase the display
before you have a shell, you are debugging blind.
