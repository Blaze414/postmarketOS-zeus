# Xiaomi 12 Pro (zeus) — chip inventory

Compiled from this device's own `/sys/firmware/fdt`, its `/vendor` partitions, and
the running mainline system. Everything here was read off the hardware, not looked up.

## Core

| | |
|---|---|
| SoC | Qualcomm **SM8450** (Snapdragon 8 Gen 1), soc_id 457, family Snapdragon |
| CPU | 8 cores: 4x Cortex-A510 (cpu0-3), 3x A710 (cpu4-6), 1x X2 (cpu7) |
| GPU | Adreno 730 (`ADRENO_7XX_GEN1`), firmware `a730_sqe.fw` + `gmu_gen70000.bin` |
| RAM | 11,177,820 kB (12 GB) |
| Storage | UFS 3.1, 234.7 GB (`sda`), plus 16 MB `sdb` |

## PMICs

Six on SPMI (`0-00` .. `0-07`), from the dts includes: **pm8350**, **pm8350b**,
**pm8350c**, **pm8450**, **pmk8350**, **pmr735a**.

Plus two **PM8008** satellite PMICs on i2c5 that cupid leaves commented out:

| | address | enable | notes |
|---|---|---|---|
| pm8008i | 0x8 / 0x9 | tlmm 7 | not wired up - nothing consumes it |
| pm8008j | 0xc / 0xd | tlmm 11 | **ldo3 = touchscreen avdd**, 3.304 V, parent `vreg_bob` |

## Display

| | |
|---|---|
| Panel (this unit) | `l2-38-0c-0a-dsc`, 1440x3200, 70x156 mm (~523 DPI) |
| Mode | DSI **command mode**, 4 lanes, DSC 1.1 (720x50 slices, 2/pkt, 10 bpc) |
| Rates | 24/30/40/60/90/120 Hz LTPO (we run fixed 60) |
| Rails | GPIO-switched fixed regulators: vddd 1.5 V tlmm 25, vci 3.0 V tlmm 75, vddio 1.8 V tlmm 74 |
| GPIOs | reset tlmm 0, TE tlmm 86 |
| Second variant | zeus also shipped `l3-42-02-0a-dsc` - the panel cupid uses |

## Touchscreen

**ST FingerTip** on **spi4** (`st,spi`, spi0.0), 12 MHz downstream.
irq tlmm 21, reset tlmm 20, avdd = pm8008j_l3, vdd = pm8350c_l2,
`tp-vendor 0x38`, firmware `st_fts_l1.ftb` + `stm_fts_production_limits.csv`.
Note the fdt also contains a `synaptics_tcm@20` node - a disabled variant, not this unit.

## Audio

**Four** Cirrus **CS35L41** smart amps on i2c1 - cupid has only two:

| addr | prefix | reset | irq | boost |
|---|---|---|---|---|
| 0x40 | BH (bottom high) | tlmm 120 | 117 | 4000 mA |
| 0x41 | BL (bottom low) | tlmm 9 | 118 | 4000 mA |
| 0x42 | TH (top high) | tlmm 3 | 63 | 4000 mA |
| 0x43 | TL (top low) | tlmm 1 | 88 | 4000 mA |

Codec: **WCD9385** (`qcom,wcd9385-codec`). Calibration blobs `BH-cs35l41-dsp1-spk-cali.bin`,
`BL-...` confirm the naming.

## Connectivity

| | |
|---|---|
| WiFi/BT | Qualcomm **WCN6855** on PCIe (`pci17cb,1103`), PMU enable tlmm 80 (wlan) / 81 (bt) |
| PCIe | perst tlmm 94, wake tlmm 96 |
| Modem | SM8450 integrated, firmware `modem.mbn` + `modem_pr/` |
| NFC | **NXP SN1xx** (`qcom,sn-nci`) on i2c |
| FM radio | **RTC6226** on i2c5 @ 0x64 |
| USB-C mux | **FSA4480** on i2c @ 0x42 (two instances), orientation tlmm 91 |

## Cameras — no mainline support

| position | sensor |
|---|---|
| wide (main) | Sony **IMX707** (Semco module) |
| ultrawide | Samsung **S5KJN1** (Sunny) |
| tele | Samsung **S5KJN1** (Sunny) |
| front | OmniVision **OV32B40** (OFilm) |

No `sm8450-camss` in mainline and no driver for any of these sensors.

## Other

| | |
|---|---|
| Haptics | **Awinic AW8697** on i2c2 @ 0x5A |
| IR blaster | `ir-spi-led` on spi13 |
| Fingerprint | **Goodix** ultrasonic (`goodix,fingerprint`) - no mainline driver |
| Buttons | power + volume-down on PMIC PON; volume-up on `pm8350_gpios` 6 |

## Firmware extracted from this device

`adsp.mbn` 23 MB, `cdsp.mbn` 7.9 MB, `slpi.mbn` 9.8 MB, `modem.mbn` 109 MB +
`modem_pr/` 47 MB, `ipa_fws.mbn`, `a730_sqe.fw`, `a730_zap.mbn`,
`gmu_gen70000.bin`, `st_fts_l1.ftb`. All merged from split `.mdt`/`.bNN` form by
`scripts/pil-squash.py`.
