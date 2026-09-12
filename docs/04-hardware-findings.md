# 04 — Hardware findings from the stock dump

Extracted from `stock-dump/zeus-stock.dts` (1.3MB decompiled) and `inventory.txt`,
pulled 2026-09-12 from the live device.

## The device is not running stock

Kernel bootargs carry:

```
mtdoops.fingerprint=EvolutionX-16.0-20260727-zeus-11.9-Unofficial
```

Root context is `u:r:ksu:s0` — **KernelSU**, not Magisk. So the dump came from
EvolutionX (Android 16) with a custom kernel, not MIUI/HyperOS.

This is fine for our purposes: custom ROMs build on Xiaomi's downstream device tree,
so the hardware description is still Xiaomi's. But if a node ever looks wrong,
cross-check against `upstream/fdt/` (extracted from HyperOS) rather than assuming
this dump is authoritative.

## Resolved: super partition

```
super -> /dev/block/sda28
```

Same as cupid. `deviceinfo_super_partitions="/dev/sda28 /dev/sda28"` — filled in,
no longer a TODO.

## Display panel

The active panel, straight from the cmdline:

```
msm_drm.dsi_display0=qcom,mdss_dsi_l2_38_0c_0a_dsc_cmd
```

Node at `zeus-stock.dts:30137`. Properties that matter for a mainline panel driver:

| Property | Value | Mainline implication |
|---|---|---|
| Mode | `dsi_cmd_mode`, `mdss-dsi-te-using-te-pin` | Command mode + TE. Needs TE GPIO wired in the dts |
| DSC | in the node name, `_dsc_` | DSC 1.1 — slice config must be transcribed exactly |
| Lanes | lane-0..3 state set | 4-lane DSI |
| Backlight | `bl_ctrl_dcs`, max `0x1fff` | DCS backlight, 13-bit. `mdss-dsi-bl-inverted-dbv` set |
| Init | `mdss-dsi-lp11-init`, `tx-eot-append` | Both need matching flags in the panel driver |
| Physical | 156mm x 70mm (`0x9c` x `0x46`) | For correct DPI |
| Panel ID | `mi,panel-id = "L2", "8\f"` | Xiaomi vendor code, not a mainline compatible |

Ignore every `mi,*` property — local HBM, FOD (fingerprint-on-display) animation,
thermal dimming. All Xiaomi userspace features with no mainline counterpart.

Extract the init command stream with the msm8916-mainline generator rather than
transcribing the hex by hand:

```bash
grep -A400 'mdss_dsi_l2_38_0c_0a_dsc_cmd {' stock-dump/zeus-stock.dts > panel-node.dts
```

## Touchscreen — RESOLVED, not a risk

An earlier read of this dump flagged `synaptics_tcm@20` as the touch controller. **That was
wrong.** That node is a disabled leftover for a panel variant this unit does not have, and
no TCM driver exists in any zeus kernel tree. The active controller is:

```dts
fts@0 {
	status = "ok";
	compatible = "st,spi";
	fts,irq-gpio  = <&tlmm 21 ...>;   // 0x15
	fts,reset-gpio = <&tlmm 20 ...>;  // 0x14
	fts,x-max = <14400>;              // 1440 x10 super-res
	fts,y-max = <32000>;              // 3200 x10
	fts,default-fw-name = "st_fts_l1.ftb";
};
```

ST Microelectronics FingerTip over **SPI**. Mainline proper has only `stmfts.c` (I2C, older
generation) — but that does not matter, because:

**`sm8450-mainline/linux` already carries `drivers/input/touchscreen/fts_spi/`,** and cupid's
mainline dts uses the identical `compatible = "st,spi"` binding with the same `fts,*` properties.

cupid vs zeus deltas are three values:

| Property | cupid | zeus |
|---|---|---|
| `fts,irq-gpio` | tlmm 21 | tlmm 21 — **same** |
| `fts,reset-gpio` | tlmm 20 | tlmm 20 — **same** |
| `fts,x-max` / `y-max` | 10800 / 24000 | 14400 / 32000 |
| `fts,default-fw-name` | `st_fts_l3.ftb` | `st_fts_l1.ftb` |

Same GPIOs. Stage 2 is a copy-paste plus two numbers and a firmware filename.
Pull `st_fts_l1.ftb` out of the stock vendor partition.

## Display panel — the naming scheme decodes

cupid's mainline panel driver is `drivers/gpu/drm/panel/panel-l3-42-02-0a-dsc.c` (451 lines),
bound to `compatible = "mdss,l3-42-02-0a-dsc"`.

Its downstream panel node was `qcom,mdss_dsi_l3_42_02_0a_dsc_cmd`. Ours is
`qcom,mdss_dsi_l2_38_0c_0a_dsc_cmd`. So the mapping is mechanical:

```
qcom,mdss_dsi_<CODE>_dsc_cmd   ->   compatible = "mdss,<code-with-dashes>-dsc"
```

zeus therefore needs:

- driver `drivers/gpu/drm/panel/panel-l2-38-0c-0a-dsc.c`
- compatible `mdss,l2-38-0c-0a-dsc`

The cupid driver is `mdss-dsi-panel-driver-generator` output — lines 45-190 are just the
DCS init stream transcribed from the downstream node. Regenerate, do not hand-write:
feed the generator zeus's `qcom,mdss-dsi-on-command` blob and it emits the `_on()` body.

Then fix the mode block for zeus's resolution (1440x3200) and re-derive the DSC slice
config from the downstream node's DSC properties.

## Firmware blobs captured

`modem.img` (448MB), `dsp.img` (64MB), `bluetooth.img` (4MB), `abl`, `xbl`,
`featenabler`, `devcfg`. These feed `rmtfs`/`pd-mapper` at Stage 7.

Gitignored — Xiaomi's proprietary blobs, not ours to redistribute.
