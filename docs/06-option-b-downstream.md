# Option B: postmarketOS on the downstream (Android 5.10) kernel

Goal: get touch working by running the vendor FTS driver in the environment it was
written for, while keeping a normal Linux userland.

## Sources (both official LineageOS, actively maintained)

| | |
|---|---|
| kernel | `LineageOS/android_kernel_xiaomi_sm8450`, branch `lineage-23.2`, **5.10.256** |
| devicetrees | `LineageOS/android_kernel_xiaomi_sm8450-devicetrees`, same branch |

`scripts/downstream-setup.sh` clones both into `/src/downstream` inside the container.
The kernel's `arch/arm64/boot/dts/Makefile` expects the devicetrees at
`arch/arm64/boot/dts/vendor`, so that is symlinked.

## What the devicetrees repo gave us immediately

Authoritative zeus **source** dts, far better than a decompiled fdt:
`zeus-sm8450.dtsi`, `zeus-pinctrl.dtsi`, `zeus-sm8450-pm8008-overlay.dts`,
`display/display/zeus-sde-display-mtp.dtsi`, `audio/zeus-audio-mtp.dts`.

It confirms every value we derived for the mainline port: touch irq 21, reset 20,
avdd `L3J` (pm8008j ldo3), vdd `L2C` (pm8350c_l2), x/y-max 14400/32000, 12 MHz,
`st_fts_l1.ftb`. **There is no devicetree fix for the mainline touch problem** - our
node was already right.

## First build attempt - where it stands

Configured with `gki_defconfig` plus `arch/arm64/configs/vendor/waipio_GKI.config`.
`CONFIG_ARCH_QCOM=y` comes through. Two blockers found:

1. **dtbs build fails on an include path.**
   `waipio-audio.dtsi:1:10: fatal error: bindings/qcom,audio-ext-clk.h`
   The devicetrees repo ships its own `bindings/` directory which is not on the dtc
   include path. Fix: add `-I$(vendor)/bindings`, or build only the zeus targets.

2. **The GKI config contains neither the touch driver nor the display driver.**
   `TOUCHSCREEN_ST_FTS_V521_SPI` does not appear in `waipio_GKI.config`. On this
   kernel generation those live as *vendor modules* built outside the kernel tree.

## The real cost of Option B

This is a fresh port, not an adjustment:

- `techpack/` in the kernel is a **stub**. The SM8450 display driver lives in an
  external `display-drivers` repo and must be built as an out-of-tree module against
  this kernel, or there is no display at all.
- Same story for audio.
- The Android GKI config has to be reworked for a normal Linux userland (pmOS has
  kconfig checks for this, but they target older monolithic downstream kernels, not
  GKI + vendor modules).
- Downstream boots base dtb + `dtbo` overlays - the mechanism we erased to make
  mainline boot. It would need restoring.

Note `arch/arm64/configs/vendor/waipio_le.config` exists - Qualcomm's Linux Embedded
config, a better starting point than the Android GKI one.

## Honest comparison

| | mainline (current) | Option B |
|---|---|---|
| display | **working** | needs display-drivers techpack built as a module |
| GPU | firmware loads, freedreno | would need Mesa KGSL backend against downstream KGSL |
| touch | broken | expected to work - vendor driver, vendor kernel |
| WiFi | PHY link never trains | expected to work |
| battery/buttons/BT | working | expected to work |
| effort remaining | unknown, likely upstream-blocked | days to weeks |

Option A (Droidian/Halium) sidesteps the techpack problem entirely, because Halium
builds the whole Android kernel tree including the vendor modules. If the goal is a
usable phone rather than a Linux-native stack, A is less work than B.
