# Speakers: writing zeus its own ADSP topology

The previous chapter ended with the sound card working and nothing audible. The
PCM ran (`state: RUNNING`, `delay: 48000`), a real sink existed, and every byte
went to wcd938x's headphone pins - which this phone does not bring out to
anything. The speakers were unreachable, and the reason was a file, not a bug.

## What was actually missing

The card asks the firmware loader for `qcom/sm8450/Xiaomi-12-tplg.bin` and
refuses to probe without it. zeus had been borrowing the SM8450 HDK's topology
by symlink. That is a fair loan - the HDK is the reference board for this SoC and
the graph is mostly SoC-level - but a topology also enumerates the *backends*,
and the HDK has no CS35L41 amps, so no backend in it reaches zeus's speakers.

A backend cannot be added from the devicetree. `audioreach_i2s_set_media_format()`
reads the interface index straight out of the topology:

```c
intf_cfg->cfg.intf_idx  = module->hw_interface_idx;   /* AR_TKN_U32_MODULE_HW_IF_IDX, token 250 */
intf_cfg->cfg.sd_line_idx = module->sd_line_idx;      /* AR_TKN_U32_MODULE_SD_LINE_IDX, token 256 */
```

The borrowed file describes primary MI2S and nothing else, so whatever the
devicetree said, the DSP was told "primary".

## Not binary surgery - the sources are public

The earlier stopping point assumed the topology would have to be edited as a
binary. It does not. Every `qcom/*-tplg.bin` in linux-firmware is generated from
m4 sources in [linux-msm/audioreach-topology], compiled with `alsatplg`, and
`SM8450-HDK.m4` - the exact file zeus was borrowing - is 90 lines of readable
macro calls. Adding a backend is one `DEVICE_SG_ADD` and two mixer/route lines.

`src/topology/Xiaomi-12.m4` is that file with the tertiary MI2S playback backend
added and nothing else touched. `scripts/gen-topology.sh` fetches the macro
library, expands it, and checks the result:

```
$ ./scripts/gen-topology.sh
==> fetching the audioreach m4 macro library
    at d1d6d8e
==> Xiaomi-12-tplg.conf  (2675 lines)
==> Xiaomi-12-sd0-tplg.conf  (2675 lines)
    Xiaomi-12-tplg.conf: tertiary backend present, fully expanded
```

Diffed against the HDK's own expansion, the entire delta is `device20.*`: one
subgraph, one container, a logger, the I2S sink module, the mixer widget and the
two graph sections that join them. The committed `.conf` files are what the
device package compiles, so a package build never needs the network.

## MI2S, not TDM

Downstream calls this port `TERTIARY_TDM_RX_0`, and audioreach has no TDM support
at all: `q6apm-lpass-dais` never sets `cfg->q6tdm_ops`, so
`q6dsp_audio_ports_set_config()` leaves `ops` NULL for every TDM dai. The
devicetree's speaker link had literally no operations behind it.

It does not need TDM. The stock devicetree configures the port as:

| property | value | meaning |
|---|---|---|
| `qcom,msm-cpudai-tdm-clk-rate` | `0x177000` | 1 536 000 Hz |
| `qcom,msm-cpudai-tdm-clk-internal` | `1` | SoC is bit-clock provider |
| `qcom,msm-cpudai-tdm-sync-mode` | `1` | long sync, 50% duty word select |
| `qcom,msm-cpudai-tdm-data-delay` | `1` | one bit clock |

1 536 000 / 48 000 = 32 bit clocks per frame: two 16-bit slots, long frame sync,
one-bit delay. That is stereo I2S wearing Qualcomm's TDM driver as a hat. An MI2S
backend describes the same wire honestly, and it is a path this kernel can drive.

(Upstream has since merged Audio-IF/TDM support - `MODULE_ID_AUDIO_IF_SINK`
`0x0700117C`, `PARAM_ID_AUDIO_IF_INTF_CFG`, `q6tdm_ops`. None of it is in
6.13-rc3, and none of it is needed for a port that is really two 16-bit slots.)

## The clock nobody was providing

With the backend in place the port still would not have made a sound, because of
two gaps that are not zeus-specific at all.

**ws_src.** `audioreach_i2s_set_media_format()` chooses the word-select source
from `cfg->fmt`:

```c
switch (cfg->fmt & SND_SOC_DAIFMT_CLOCK_PROVIDER_MASK) {
case SND_SOC_DAIFMT_BP_FP: intf_cfg->cfg.ws_src = CONFIG_I2S_WS_SRC_INTERNAL; break;
case SND_SOC_DAIFMT_BC_FC: intf_cfg->cfg.ws_src = CONFIG_I2S_WS_SRC_EXTERNAL; break;
default: break;
}
```

`cfg->fmt` is only ever written by `q6i2s_set_fmt()`, and `q6i2s_ops` did not
list `.set_fmt` - only `q6hdmi_ops` did. So `fmt` was 0, no case matched, and
`ws_src` kept its zero value, which is `CONFIG_I2S_WS_SRC_EXTERNAL` (0x0). The
DSP waited for a bit clock from a codec that was waiting for one back.

Nothing was going to write it either: `qcom_snd_parse_of()` does not look at
`dai-format`, and no machine driver in this family calls
`snd_soc_dai_set_fmt()` on a backend.

**SCLK.** CS35L41 runs its whole digital section off a PLL locked to SCLK and
produces silence until it is told the rate. It splits that across two callbacks -
the component one programs the PLL, the DAI one sizes the clock monitor - and
`snd_soc_dai_set_sysclk()` calls only the DAI op when a codec has both. Calling
one is the same as calling neither.

`0009-asoc-qcom-give-mi2s-backends-a-clock.patch` closes both: `.set_fmt` on
`q6i2s_ops`, `snd_soc_runtime_set_dai_fmt(..., CBC_CFC)` for MI2S backends in
`sc8280xp_snd_init()`, and both sysclk calls in `hw_params` at
`rate * channels * width` - 48000 x 2 x 16 = 1 536 000, matching the stock
`clk-rate` exactly.

## The one thing that is a guess

Which serial data line the amps listen on. The pins are:

```
gpio121  mi2s2_sck    tert_tdm_clk
gpio123  mi2s2_ws     tert_tdm_ws
gpio122  mi2s2_data0  tert_tdm_din    -> SD0
gpio124  mi2s2_data1  tert_tdm_dout   -> SD1
```

Qualcomm's audio pinctrl names are written from the SoC's point of view, so
"dout" is the line the SoC drives: SD1. That is the default. The stock devicetree
does not say so outright, and LPASS lets either line carry either direction, so
this is inference rather than fact.

Which is why both are built. A topology is an ordinary firmware file, so trying
the other line is:

```sh
cd /lib/firmware/qcom/sm8450
mv Xiaomi-12-tplg.bin Xiaomi-12-sd1-tplg.bin
cp Xiaomi-12-sd0-tplg.bin Xiaomi-12-tplg.bin
reboot
```

A reboot, not a reflash.

## Known limits

- **Mono.** Mainline's CS35L41 takes its channel from `set_channel_map`, and
  nothing calls it here, so all four amps read slot 0. Stock marks BH and BL as
  right-channel amps and TH/TL as left; reproducing that needs a per-codec
  channel map from the machine driver. Sound first, stereo after.
- **No speaker protection.** The Cirrus DSP firmware and the per-amp calibration
  blobs in `/vendor/firmware` are not loaded, so `PCM Source` is set to `ASP`
  (straight through) and `Analog PCM Volume` is held at 10 of a possible 20.

[linux-msm/audioreach-topology]: https://github.com/linux-msm/audioreach-topology

## Outcome on hardware: rejected by the DSP, and reverted

Flashed and tested. The backend exists and DAPM routes to it, but the ADSP
refuses the subgraph at `APM_CMD_GRAPH_OPEN` (`Error (1) Processing 0x01001000`),
the amps then time out waiting for a clock (`cs35l41: Enable(1) failed: -110`),
and the failed open poisons the APM badly enough that the headphone path
(`RX_CODEC_DMA_RX_0`) fails the same way. Same kernel, topology swapped back to
the HDK's: 0 DSP errors and a real sink again. So this topology was a net
regression and is **not shipped**; its sources stay in `src/topology/`.

Each suspect was changed alone, one reboot each, with the Speaker UCM device
enabled so the backend was actually opened:

| variant | GRAPH_OPEN failures |
|---|---|
| SD1 (`SD_LINE_IDX 2`) | rejected |
| SD0 (`SD_LINE_IDX 1`) | rejected |
| SD0 + `HW_IF_IDX 0` - token-for-token the primary block | rejected |
| SD0 + `MODULE_ID_AUDIO_IF_SINK 0x0700117C` | rejected (205) |

Caution for anyone repeating this: counting errors a few seconds after boot
reads 0 for every variant, because PulseAudio has not retried yet. The first
AUDIO_IF reading looked like success for exactly that reason.

With the SD line, interface index and module id all ruled out, the tertiary
block differs from the primary one only in its instance ids and DAI index. Every
path that works on this device is CODEC_DMA; no I2S subgraph - primary included
- has ever been shown to open here. The open question is therefore whether this
vendor SPF build instantiates LPASS I2S from a dynamic graph at all, which is not
something more topology variants can answer.

## Also found: the post-install never ran

The `-openrc` post-install is recorded in the rootfs (`scripts.tar.gz`) but
never executed during `pmbootstrap install`. That one silent miss removed the
qbootctl runlevel, the OSK autostart and the notch overlay. The device package
now ships those as plain files and symlinks, plus
`/etc/modules-load.d/zeus.conf` for `fts_touch_spi`, which was never being
autoloaded. `pd-mapper` was retried and is still a dead end.

## Bit clock vote: works, and is not the blocker

Mainline votes each MI2S port's bit clock through q6prm before the graph opens;
6.13 never did. `0010-asoc-qcom-vote-the-lpass-i2s-bit-clock.patch` backports
that (per-dai `bclk` from `q6prmcc`, enabled from the machine driver's
`hw_params`), with a `dai@14` node naming `LPASS_CLK_ID_TER_MI2S_IBIT`.

On hardware the vote succeeds - debugfs shows `LPASS_CLK_ID_TER_MI2S_IBIT`
with `clk_enable_count=1`, `clk_rate=1536000`, no PRM errors - and
`APM_CMD_GRAPH_OPEN` is still rejected (1036 times in five minutes). The patch
stays: it is what mainline does and costs nothing while no MI2S graph opens.

The four amps are two woofers and two tweeters (Harman Kardon tuning), so even
a working backend would need a per-amp channel/crossover split before it sounds
right.

The remaining unknown is what module and interface this vendor SPF build
expects for the port. The authoritative record is Android's own ACDB on the
vendor partition, which lists the module IDs of the speaker graph this exact
firmware runs.

## Flashing lesson

Every `pmbootstrap install` gives the root filesystem a new UUID, and boot.img's
cmdline names it. Flashing only a newly built boot.img onto an older rootfs
stops in the initramfs ("failed to mount subpartitions", debug shell on :23).
Flash boot and root together, or rewrite `pmos_root_uuid`/`pmos_boot_uuid` in
the image to the installed rootfs's values first.
