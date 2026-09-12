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

## Audit: what in the dts is actually zeus (2026-09-12)

The dts was derived from cupid, so the risk is inherited-but-wrong nodes. Diffing our dts
against cupid's shows only the nine intended edits — which is exactly the problem: every
*other* node is cupid's description, silently assumed to apply.

Method: for each board-level node, resolve the downstream phandles in this device's own fdt
and compare against cupid's HyperOS fdt (`upstream/fdt/cupid.dts`) field by field.

### Power topology is different — two real bugs found and fixed

**Panel rails.** cupid drives its panel from pm8350c LDOs. zeus drives the l2 panel from
**GPIO-switched fixed regulators**:

| rail | cupid | zeus | voltage |
|---|---|---|---|
| `vddd` | `pm8350c_l10` | fixed, `tlmm 25` | 1.5 V |
| `vci` | `pm8350c_l13` | fixed, `tlmm 75` | 3.0 V |
| `vddio` | `pm8350c_l12` | fixed, `tlmm 74` | 1.8 V |

Inherited unchanged, this leaves the panel unpowered while enabling three unrelated rails —
a dark screen that looks exactly like a bad panel driver.

Note the *secondary* display path in zeus's downstream tree (the l3 panel variant, the one
cupid uses) does route to `pm8350c_l13`/`l12`. So cupid's values are not wrong in general;
they are wrong for *our* panel. Same board, two supply topologies.

**Touchscreen avdd.** Same comparison, unambiguous:

```
cupid  avdd-supply = <&L7C>    -> pm8350c_l7
zeus   avdd-supply = <0x5a8>   -> pm8008j_l3, 3.3V
```

zeus carries two **PM8008 satellite PMICs** on i2c5 — `pm8008i @ 0x8` (irq/reset tlmm 7)
and `pm8008j @ 0xc` (irq/reset tlmm 11). cupid's mainline dts has them commented out as
`/* pm8008j @ c */` placeholders, because nothing on cupid needs them. On zeus the
touchscreen does.

Mainline has the drivers: `drivers/mfd/qcom-pm8008.c` and
`drivers/regulator/qcom-pm8008-regulator.c`, symbols `MFD_QCOM_PM8008` and
`REGULATOR_QCOM_PM8008`, both now in the config fragment.

No GPIO conflicts: pm8008 uses tlmm 7 and 11, the panel rails 25/74/75.

### Verified the same, left alone

| | result |
|---|---|
| touch controller, bus, GPIOs | ST FTS on spi4, irq tlmm 21, reset tlmm 20 — identical |
| touch `vdd` | `pm8350c_l2` on both |
| panel reset / TE GPIOs | tlmm 0 / tlmm 86 — identical |
| audio | `cs35l41` amps + `aw8697` haptic on both |
| SoC, PMICs, UFS, USB, WiFi/BT | shared silicon, no board delta expected |

### Still unverified

- **`vdd-l3-l4-supply` for pm8008j** — set to `vreg_bob`, matching how other mainline boards
  feed a PM8008. The downstream tree does not spell the routing out.
- **Battery and charging parameters** — inherited from cupid, not checked. zeus is a
  different cell and a 120W charger.
- **Panel regulator enable ordering / post-on delays** — downstream specifies
  `supply-post-on-sleep = 1` per rail; the fixed-regulator model does not express that.
- `pm8008i @ 0x8` is left undescribed; nothing consumes it yet.
