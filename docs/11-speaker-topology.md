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

## Stock actually uses TDM_SINK at 8 x 32-bit - implemented, still rejected

Read from the phone's own vendor partition:

- `resourcemanager_waipio_mtp.xml`: speaker backend `TDM-LPAIF-RX-TERTIARY-VIRT-0`,
  2 channels, 24-bit, amps with `PCM Source = DSP` (Cirrus firmware).
- ACDB `Mise_elus_acdb_cal.acdb`: `MODULE_ID_TDM_SINK` (0x0700100E, from SPF's
  `pcm_tdm_api.h`) appears 61 times; `I2S_SINK` and `AUDIO_IF_SINK` never.
- Downstream `msm_common.c`: 32-bit slots, `qcom,tdm-max-slots = <8>` on zeus,
  bit clock `CLOCK_ID_TER_TDM_IBIT` (0x204) at rate x 32 x 8 = 12.288 MHz.
  (The DT's `clk-rate = 0x177000` is not what runs.)
- `adsp.mbn` contains the driver statically (`capi_pcm_tdm_island.c`).

`0011-asoc-qcom-drive-the-speakers-through-tdm-sink.patch` implements that:
`PARAM_ID_TDM_INTF_CFG` for TDM_SINK, TDM dai ops, the TER_TDM_IBIT PRM clock,
S32 on the backend, slots 0/1, per-amp channel from the name prefix. The
speaker link and a `dai@38` clock node now name `TERTIARY_TDM_RX_0`.

On hardware the clock is set to 12288000 Hz without error, and
`APM_CMD_GRAPH_OPEN` is still rejected - both with the plain endpoint subgraph
and rebuilt on the exact codec-path template (logger -> MFC -> endpoint) that
opens fine for headphones, i.e. the only remaining difference is the endpoint
module on LPAIF interface 2. The DSP returns bare AR_EFAILED; its reason goes to
its own diag log. Reading that log (Qualcomm diag over the DSP's diag channel)
is the next step rather than more guessed variants.

## Reading the DSP's own log

`scripts/diag/`: linux-msm `diag-router` built on the phone, plus `diagcat.py`,
a minimal client that switches on all F3 message masks and prints them. Two
gotchas on the way:

- diag-router segfaults on "set all message masks": it broadcasts with a NULL
  range and `diag_cmd_get_msg_mask()` dereferences it. One-line fix: default the
  range to the dummy range in `diag_cntl_send_msg_mask()`.
- Most SPF messages (SSID 8500) are QShrink-hashed. The only QDB on the phone's
  partitions is the modem's (`image/waipio/qdsp6m.qdb`, MPSS); there is no ADSP
  QDB, so hashed messages stay hashes. Readable ones and opcode arguments are
  still informative.

Findings, all on the TDM_SINK topology with the Speaker UCM device off and the
path driven by hand with PulseAudio's sink suspended:

1. **The speaker graph opens.** The earlier `GRAPH_OPEN` rejections happened
   only while PulseAudio was driving both backends at once.
2. **The endpoint runs but starves.** `MODULE:60a2, Underrun detected ...
   media_format_set: 0` and `Ext input port 0x2 of Module 0x60a0, actual data
   len 0`; the stream consumes at most one buffer.
3. **The kernel sends the FE->BE connection correctly** (debug print: graph 56
   opens with `src=0x6006 dst=0x60a0`, same shape as headphones' graph 113 with
   `0x6006 -> 0x6070`).
4. **Headphones pass the identical fresh-open sequence** (12 buffer-dones, no
   underrun), so this is specific to the speaker endpoint, not graph handling.
5. **Not the sample format**: S16 end to end starves the same way as S32.
6. Headphone opens log `0x100100f` / `0x100102c` for their subgraph; the
   speaker open never produces those - the DSP does not form the link for the
   TDM subgraph. Without the ADSP QDB the reason stays behind a hash.

The saved session is `stock-dump/diag-speaker-session.log`.

## Stock graph, from the phone's ACDB

`scripts/acdb/` builds AudioReach graphservices' own ACDB parser and queries
`Mise_elus_acdb_cal.acdb` as Android does (483 graph key vectors). Speaker
playback is `STREAMRX=0xA1000003, DEVICERX=0xA2000001` (dumps in
`stock-dump/audio/spk-graph.txt`, headphones in `hp-graph.txt`).

- Device subgraph, one GC container at graph position "global device":
  `0x07001010 -> 0x07001015 -> SPLITTER -> MUX_DEMUX -> DATA_LOGGING -> TDM_SINK`,
  fed from the stream's `0x07001015` into input port 4.
- Stream subgraph, SC container: `DATA_LOGGING -> 0x0700101B -> 0x07001015`.
- TDM_SINK static calibration: `HW_EP_MF_CFG`, `FRAME_SIZE_FACTOR=1`,
  **`PARAM_ID_TDM_LANE_CFG = 2`** (data line 1, gpio124) and
  `PARAM_ID_HW_INTF_CLK_CFG` with clock attribute 4 (inverted). The only
  calibration key is volume, so `TDM_INTF_CFG` is set at runtime.

Patch 0011 now also sends `PARAM_ID_TDM_LANE_CFG`. The DSP accepts it
(`SET_CFG` result 0). Matching the stock subgraph direction (RX) and container
(GC, global-device position, 4 KB stack) was also tried. The speaker endpoint
still starves.

Two things measured along the way:
- The TDM bit clock really is enabled during playback (debugfs
  `LPASS_CLK_ID_TER_TDM_IBIT` enable=1, 12288000 Hz), and the endpoint
  underruns once per 1 ms frame, so LPASS TDM is running.
- In the DSP log, `0x0100100F`/`0x01001010` are `PRM_CMD_REQUEST/RELEASE_HW_RSC`,
  not graph commands.

A stub-codec test (speaker link on `linux,spdif-dit` instead of the amps) oopses
in `qcom_snd_sdw_startup` and wedges the card, so it cannot separate DSP from amp
timing without first guarding that path.

## Amp timing and graph start order: both ruled out

- **SoundWire stream on non-SoundWire backends.** `qcom_snd_sdw_startup()` was
  run for the MI2S/TDM speaker link too; with a codec DAI that has no ops it
  NULL-dereferences inside `snd_soc_dai_set_stream()` and leaves the card lock
  held (every later `amixer` stuck in D state). Patch 0011 now skips the
  SoundWire stream for MI2S/TDM backends.
- **Amps out of the link.** With the speaker link pointed at a
  `linux,spdif-dit` stub instead of the four CS35L41s, the TDM endpoint still
  starves (22 underruns, 2 buffer-dones). The amps' I2C setup delay is not the
  cause.
- **Graph start order.** 6.13 starts the backend graph from `prepare`, before
  the stream graph; mainline starts it from `trigger START`.
  `0012-asoc-qcom-q6apm-lpass-dais-start-graph-on-trigger.patch` backports that
  (headphones still flow, so trigger reaches the backend). Speakers still
  starve, with S32 and with S16 on the backend.

With amps, clocks, lane, format, start order and container/subgraph properties
all matched or ruled out, the speaker subgraph differs from the working
headphone one only in the endpoint module (TDM_SINK on LPAIF tertiary) and the
modules stock places ahead of it. Stock's device chain starts with
`0x07001010`/`0x07001015`/SPLITTER/MUX_DEMUX, none of which exist in this
topology.

## "Headphones" is not audible either

The phone has no 3.5 mm jack. wcd938x's headphone output only reaches a USB-C
analog dongle through the Type-C audio switch (`typec-mux@42` on i2c), which has
to enter audio-accessory mode. Nothing drives that yet, so the headphone path
consuming data in the DSP does not mean sound comes out of a dongle.

## USB-C audio works

`CONFIG_SND_USB_AUDIO` was not set, so USB Audio Class devices enumerated in
host mode but got no driver. Enabled as a module (0411d4f). Confirmed on
hardware: a BLUEANT SOUNDBLADE USB-C speaker registers as card 1 and plays
through PulseAudio, and USB-C headphones work. This is independent of the ADSP,
so it is currently the only working audio output on the phone. Passive analog
USB-C adapters still need the Type-C audio switch driven.

## 96 kHz / 24-bit, as the ACDB calibrates it: still starves

The stock ACDB calibrates the speaker TDM_SINK and the MFC ahead of it at
96000 Hz / 24-bit. Running the backend that way (fixup to 96 kHz S24 in 32-bit
slots, bit clock 24.576 MHz) negotiates fine - CS35L41's PLL accepts 24.576 MHz,
only its clock-monitor table lacks it - and the endpoint still starves (27
underruns, 2 buffer-dones). Not kept.

What has now been matched or excluded: module ID, interface index, data line
(lane), bit clock (verified running), sync shape, sample rate and width, graph
start order, subgraph direction, container type/position/stack, amps (stub
codec). What has not: the four stock modules ahead of the endpoint and their
calibration, which is ACDB data 6.13's topology path has no way to carry.

The most direct remaining route is to reproduce the stock graph byte for byte:
send the ACDB's own GRAPH_OPEN payload, connections and calibration blobs
(already dumped by scripts/acdb) to the APM from the kernel, bypassing the
topology for this one backend.

## Stock graph replayed from the ACDB: the TDM endpoint consumes

Patch `0013-asoc-qcom-q6apm-open-graphs-from-vendor-blobs.patch` lets q6apm
send `qcom/apm-graph-<id>.bin` as the GRAPH_OPEN payload and
`qcom/apm-graph-<id>-cal.bin` as SET_CFG, instead of the topology-built packet.
`scripts/acdb/mkgraph.py` builds both from `stock-dump/audio/spk-graph.txt`:
the stock device subgraph (0x07001010 -> MFC -> SPLITTER -> MUX_DEMUX -> logger
-> TDM_SINK) with its SG/container/logger/MFC/TDM ids renamed onto topology
graph 56 (so the kernel's prepare/start/close and media-format params still
address them), splitter links to unopened subgraphs dropped, and MultiMedia1's
logger (0x6006) connected into 0x07001010 input port 4 as stock does.

With `Xiaomi-12-tdm-mfc-tplg.bin` and the two blobs in `/lib/firmware/qcom/`:
0 underruns, 11 buffer-dones in 5 s, media format 48000 Hz reaches the
splitter, TDM_SINK timestamps advance, speaker-test runs in real time (6.0 s per
3 s x 2 channels), no DSP errors. First time the speaker endpoint has consumed
data. Audibility not yet confirmed. Amp 0x40 read GLOBAL_EN=1 during playback.
