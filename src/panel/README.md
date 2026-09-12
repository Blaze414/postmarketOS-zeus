# zeus panel — spec for `panel-l2-38-0c-0a-dsc.c`

Source of truth: `zeus-panel-node.dts` (829 lines, extracted from the live device fdt at
`zeus-stock.dts:30137`). Target compatible: `mdss,l2-38-0c-0a-dsc`.

Template: `drivers/gpu/drm/panel/panel-l3-42-02-0a-dsc.c` (cupid, 451 lines).

## Decoded timings

From the downstream node, hex converted:

| Downstream property | Hex | Value |
|---|---|---|
| `panel-width` | `0x5a0` | 1440 |
| `panel-height` | `0xc80` | 3200 |
| `h-front-porch` | `0x20` | 32 |
| `h-pulse-width` | `0x10` | 16 |
| `h-back-porch` | `0x20` | 32 |
| `v-front-porch` | `0x18` | 24 |
| `v-pulse-width` | `0x08` | 8 |
| `v-back-porch` | `0x18` | 24 |
| `bpp` | `0x1e` | 30 (10bpc x3) |
| `panel-clockrate` | `0x510ff400` | 1360065536 |
| physical size | `0x46` x `0x9c` | 70mm x 156mm |

Supported framerates (LTPO): `0x18 0x1e 0x28 0x3c 0x5a 0x78` = 24, 30, 40, 60, 90, 120 Hz.
**Bring up at 60 Hz first.** Multi-mode LTPO switching is a later problem; a fixed-mode
panel driver is what `drm_connector_helper_get_modes_fixed()` wants and cupid does the same.

## drm_display_mode block

```c
static const struct drm_display_mode l2_38_0c_0a_dsc_mode = {
	.clock = (1440 + 32 + 16 + 32) * (3200 + 24 + 8 + 24) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 32,
	.hsync_end = 1440 + 32 + 16,
	.htotal = 1440 + 32 + 16 + 32,	/* 1520 */
	.vdisplay = 3200,
	.vsync_start = 3200 + 24,
	.vsync_end = 3200 + 24 + 8,
	.vtotal = 3200 + 24 + 8 + 24,	/* 3256 */
	.width_mm = 70,
	.height_mm = 156,
	.type = DRM_MODE_TYPE_DRIVER,
};
```

Pixel clock works out to 296,947 kHz at 60 Hz (593,894 at 120).

## DSC config

Downstream says:

| Property | Value |
|---|---|
| `mdss-dsc-slice-width` | `0x2d0` = 720 |
| `mdss-dsc-slice-height` | `0x32` = 50 |
| `mdss-dsc-slice-per-pkt` | 2 |
| `mdss-dsc-bit-per-component` | 10 |
| `mdss-dsc-bit-per-pixel` | 8 |
| `mdss-dsc-block-prediction-enable` | present |

So in probe:

```c
ctx->dsc.dsc_version_major = 1;
ctx->dsc.dsc_version_minor = 1;
ctx->dsc.slice_width = 720;		/* two slices across 1440 */
ctx->dsc.slice_height = 50;		/* 3200 / 50 = 64 slices down, exact */
ctx->dsc.slice_count = 2;
ctx->dsc.bits_per_component = 10;
ctx->dsc.bits_per_pixel = 8 << 4;	/* DSC bpp is 4-bit fixed point */
ctx->dsc.block_pred_enable = true;
```

Both divisions are exact (1440/720, 3200/50), which is a good sign the values are right —
DSC slice dims must divide the active area evenly.

Note cupid's driver carries `/* TODO: Pass slice_per_pkt = 1 */` and hardcodes
`slice_width = 1080` (full width, one slice). zeus genuinely uses two slices per line,
so this is a real difference, not a copy target.

## Other panel properties that map to driver flags

| Downstream | Driver implication |
|---|---|
| `mdss-dsi-te-using-te-pin`, `te-pin-select = 1` | `te-gpios` in the dts node |
| `mdss-dsi-lp11-init` | `dsi->mode_flags |= MIPI_DSI_MODE_LPM` during init |
| `mdss-dsi-tx-eot-append` | do NOT set `MIPI_DSI_MODE_NO_EOT_PACKET` |
| `bl-pmic-control-type = "bl_ctrl_dcs"` | DCS backlight, as cupid |
| `mdss-dsi-bl-max-level = 0x7ff` / `brightness-max = 0x1fff` | 11-bit DCS, 13-bit UI scale |
| `mdss-dsi-bl-inverted-dbv` | brightness bytes are byte-swapped vs cupid — check this if backlight behaves backwards |
| `dsi_cmd_mode` | command mode, so no `MIPI_DSI_MODE_VIDEO*` flags (cupid's `MIPI_DSI_MODE_VIDEO_BURST` is wrong for us) |

Ignore every `mi,*` property (local HBM, FOD animation, thermal dimming) — Xiaomi userspace
features with no mainline counterpart.

## Generating the driver

Do not hand-transcribe the init command stream. Lines 45-190 of cupid's driver are machine
output. Run `scripts/gen-panel.sh`.

## zeus ships two panel variants

The HyperOS devicetree (`upstream/fdt/zeus.dts`) carries **both**:

- `qcom,mdss_dsi_l2_38_0c_0a_dsc_cmd`  ← **this unit** (per the live cmdline)
- `qcom,mdss_dsi_l3_42_02_0a_dsc_cmd`  ← the *same panel cupid uses*

So zeus was sold with two different panel suppliers. A zeus with the l3 panel would work
with the existing `panel-l3-42-02-0a-dsc.c` driver and need no panel work at all.

Ours is l2, confirmed from the running kernel's cmdline:

```
msm_drm.dsi_display0=qcom,mdss_dsi_l2_38_0c_0a_dsc_cmd
```

Which means: the dts should eventually declare **both** panels and let the panel-ID probe
pick, exactly as downstream does. For first boot, hardcode l2 and move on.

## Which dump to trust

Two zeus devicetrees are now on disk:

| File | Source | Use |
|---|---|---|
| `src/panel/zeus-panel-node.dts` | live `/sys/firmware/fdt`, this device | **authoritative for this unit** |
| `upstream/fdt/zeus.dts` | HyperOS, pretty-printed by a third party | cross-reference only |

The HyperOS copy has phandle-resolution artifacts — it renders
`qcom,mdss-dsc-slice-height = <&apss_atb_cti>`, which is nonsense; the pretty-printer
resolved integer values into unrelated node references. Our live dump has real numbers.
Use it, and treat the HyperOS copy as a second opinion on *structure*, never on *values*.

## Generated — status

`panel-l2-38-0c-0a-dsc.c` (400 lines) was produced by `scripts/gen-panel.sh` from
`stock-dump/zeus-stock.dtb` and promoted to `src/panel/`. Verification against the
hand-derived spec above: the generator's `drm_display_mode` matched it **exactly**
(1440+32/16/32, 3200+24/8/24, 70x156mm), and its DSC block derives
`slice_count = 1440 / 720 = 2` on its own.

Required a one-line patch to the generator — it rejected `bpp = 30` (10bpc) outright.
See `patches/0001-panel-generator-support-30bpp-dsc.patch`. There is no 30bpp MIPI DSI
pixel format; DSC panels carry a compressed stream that mainline drives as RGB888,
which is what cupid's driver does too.

### Resolved from downstream, already applied

| | value | note |
|---|---|---|
| `reset-gpios` | `&tlmm 0 GPIO_ACTIVE_LOW` | same pin as cupid |
| `te-gpios` | `&tlmm 86 GPIO_ACTIVE_HIGH` | same pin as cupid (`0x56`) |

### Open question — `MIPI_DSI_MODE_VIDEO_BURST`

The generator emits:

```c
dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST |
		  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;
```

zeus is a **command-mode** panel (`dsi_cmd_mode`, `te-using-te-pin`, `mdp-trigger = "none"`,
`dma-trigger = "trigger_sw"`), so `MIPI_DSI_MODE_VIDEO_BURST` looks wrong on its face.

**Left as-is deliberately.** cupid is also a command-mode panel, its driver carries the same
flag, and cupid works. Either the qcom DSI host wants it or it is inert on this path.
Do not "fix" this before first boot — if the panel stays dark, dropping `VIDEO_BURST`
is the *first* thing to try, but changing it now means debugging two deltas at once.

### Still outstanding

- `slice_per_pkt = 2` — the generator left a TODO, as it did for cupid. Mainline's
  `drm_dsc_config` has no slice-per-packet field; may need host-side handling.
- LTPO: only the first of six timings was generated ("Multiple display timings are not
  supported yet, using first!"). 60 Hz fixed for now, which is what we want for bring-up.

## Compiles (2026-09-12)

`panel-l2-38-0c-0a-dsc.o`, 51744 bytes, no warnings. Two fixes were needed after the
first generation, both found by actually compiling rather than by reading:

### 1. The driver had no regulators

The first generator run produced a driver that never requested the panel's power supplies,
while our dts (inherited from cupid) declares `vddd`/`vci`/`vddio`. The panel would have
stayed dark with nothing in the log to say why.

Fixed by regenerating with the supplies named explicitly:

```bash
lmdpdg.py -r vddd -r vci -r vddio stock-dump/zeus-stock.dtb
```

The generator does not infer supplies from the downstream node - it has to be told.

### 2. The generator targets a newer kernel than the fork

It emits `devm_drm_panel_alloc()`, which landed in 6.15. `sm8450-mainline/linux` `next-new`
is **6.13.0-rc3**, so the build failed with `implicit declaration of function`.

Backported to the 6.13 pattern, which is exactly what cupid's driver does:

```c
ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
if (!ctx)
	return -ENOMEM;
...
drm_panel_init(&ctx->panel, dev, &l2_38_0c_0a_dsc_panel_funcs,
	       DRM_MODE_CONNECTOR_DSI);
```

This is a **regeneration hazard**: re-running `gen-panel.sh` will reintroduce the 6.15 API.
Either keep the edit or rebase the kernel forward. The unused-`panel_funcs` warning that
appeared alongside the error was the tell - the funcs struct was only referenced from the
alloc call the old API does not have.

### Registration

`scripts/build.sh` registers all four touchpoints idempotently, asserting each landed:

| File | Entry |
|---|---|
| `drivers/gpu/drm/panel/Kconfig` | `config DRM_PANEL_XIAOMI_38_0C_0A` |
| `drivers/gpu/drm/panel/Makefile` | `obj-$(CONFIG_DRM_PANEL_XIAOMI_38_0C_0A) += panel-l2-38-0c-0a-dsc.o` |
| `arch/arm64/configs/sm8450.config` | `CONFIG_DRM_PANEL_XIAOMI_38_0C_0A=m` |
| `arch/arm64/boot/dts/qcom/Makefile` | `dtb-$(CONFIG_ARCH_QCOM) += sm8450-xiaomi-zeus.dtb` |

Touch needs no new symbol: `CONFIG_TOUCHSCREEN_ST_FTS_V521_SPI=m` is already in the
fork's sm8450 fragment, enabled for cupid, and our controller is the same driver.
