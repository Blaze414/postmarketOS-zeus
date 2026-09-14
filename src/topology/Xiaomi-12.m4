# Topology for the Xiaomi 12 Pro (zeus).
# Copyright, Linaro Ltd, 2023
# SPDX-License-Identifier: BSD-3-Clause
#
# Derived from SM8450-HDK.m4 in https://github.com/linux-msm/audioreach-topology,
# which is what zeus was borrowing wholesale until now. Everything the HDK
# describes is kept verbatim; the addition is the Tertiary MI2S playback
# backend, which is the only thing on this board that reaches the speakers.
#
# Why MI2S and not TDM: the four CS35L41 amps hang off tertiary LPASS, and the
# stock devicetree configures that port at
#
#   qcom,msm-cpudai-tdm-clk-rate     = <0x177000>   /* 1 536 000 Hz */
#   qcom,msm-cpudai-tdm-clk-internal = <1>          /* SoC is bit-clock master */
#   qcom,msm-cpudai-tdm-sync-mode    = <1>          /* long sync, 50% duty WS */
#   qcom,msm-cpudai-tdm-data-delay   = <1>
#
# 1 536 000 / 48 000 = 32 bit clocks per frame, i.e. two 16-bit slots with a
# one-bit data delay and a long frame sync. That is plain stereo I2S wearing
# Qualcomm's TDM driver as a hat, so an MI2S backend is a faithful description
# of the wire and not a compromise. It also sidesteps the fact that this
# kernel's audioreach has no TDM support at all: q6dsp_audio_ports_set_config()
# leaves ops NULL for PRIMARY_TDM_RX_0..QUINARY_TDM_TX_7 because
# q6apm-lpass-dais never sets cfg->q6tdm_ops.
#
# The SD line is the one thing the stock devicetree does not spell out. Pins:
#
#   gpio121  mi2s2_sck     tert_tdm_clk
#   gpio123  mi2s2_ws      tert_tdm_ws
#   gpio122  mi2s2_data0   tert_tdm_din    -> SD0
#   gpio124  mi2s2_data1   tert_tdm_dout   -> SD1
#
# Qualcomm's audio pinctrl names are written from the SoC's point of view, so
# "dout" is the line the SoC drives and the amps listen on: SD1. That is the
# default here. Build with -DZEUS_SPK_SD0 to get the other one - the topology is
# an ordinary firmware file, so swapping between the two is a symlink and a
# reboot, not a reflash.
define(`ZEUS_SPK_SD_LINE', `ifdef(`ZEUS_SPK_SD0', SD_LINE_IDX_I2S_SD0, SD_LINE_IDX_I2S_SD1)') dnl
include(`audioreach/audioreach.m4')
include(`audioreach/stream-subgraph.m4')
include(`audioreach/device-subgraph.m4')
include(`util/route.m4')
include(`util/mixer.m4')
include(`audioreach/tokens.m4')
#
# Stream SubGraph  for MultiMedia Playback
#
#  ______________________________________________
# |               Sub Graph 1                    |
# | [WR_SH] -> [PCM DEC] -> [PCM CONV] -> [LOG]  |- Kcontrol
# |______________________________________________|
#
dnl Playback MultiMedia1
STREAM_SG_PCM_ADD(audioreach/subgraph-stream-vol-playback.m4, FRONTEND_DAI_MULTIMEDIA1,
	`S16_LE', 48000, 48000, 2, 2,
	0x00004001, 0x00004001, 0x00006001)
dnl Playback MultiMedia2
STREAM_SG_PCM_ADD(audioreach/subgraph-stream-vol-playback.m4, FRONTEND_DAI_MULTIMEDIA2,
	`S16_LE', 48000, 48000, 2, 2,
	0x00004002, 0x00004002, 0x00006010)
dnl Capture MultiMedia3
STREAM_SG_PCM_ADD(audioreach/subgraph-stream-capture.m4, FRONTEND_DAI_MULTIMEDIA3,
	`S16_LE', 48000, 48000, 1, 2,
	0x00004003, 0x00004003, 0x00006020)
dnl Capture MultiMedia4
STREAM_SG_PCM_ADD(audioreach/subgraph-stream-capture.m4, FRONTEND_DAI_MULTIMEDIA4,
	`S16_LE', 48000, 48000, 1, 2,
	0x00004004, 0x00004004, 0x00006030)
#
#
# Device SubGraph  for WSA RX0 Backend
#
#         ___________________
#        |   Sub Graph 2     |
# Mixer -| [LOG] -> [WSA EP] |
#        |___________________|
#
dnl DEVICE_SG_ADD(stream, stream-dai-id, stream-index,
dnl 	format, min-rate, max-rate, min-channels, max-channels,
dnl	interface-type, interface-index, data-format,
dnl	sg-iid-start, cont-iid-start, mod-iid-start
dnl WSA Playback
DEVICE_SG_ADD(audioreach/subgraph-device-codec-dma-playback.m4, `WSA_CODEC_DMA_RX_0', WSA_CODEC_DMA_RX_0,
	`S16_LE', 48000, 48000, 2, 2,
	LPAIF_INTF_TYPE_WSA, CODEC_INTF_IDX_RX0, 0, DATA_FORMAT_FIXED_POINT,
	0x00004005, 0x00004005, 0x00006050)
dnl
dnl Primary MI2S Playback
DEVICE_SG_ADD(audioreach/subgraph-device-i2s-playback.m4, `Primary', PRIMARY_MI2S_RX,
	`S16_LE', 48000, 48000, 2, 2,
	LPAIF_INTF_TYPE_LPAIF, I2S_INTF_TYPE_PRIMARY, SD_LINE_IDX_I2S_SD0, DATA_FORMAT_FIXED_POINT,
	0x00004006, 0x00004006, 0x00006060, `PRIMARY_MI2S_RX')
dnl
dnl WCDRX Playback
DEVICE_SG_ADD(audioreach/subgraph-device-codec-dma-playback.m4, `RX_CODEC_DMA_RX_0', RX_CODEC_DMA_RX_0,
	`S16_LE', 48000, 48000, 2, 2,
	LPAIF_INTF_TYPE_RXTX, CODEC_INTF_IDX_RX0, 0, DATA_FORMAT_FIXED_POINT,
	0x00004007, 0x00004007, 0x00006070)
dnl
dnl VA Capture
DEVICE_SG_ADD(audioreach/subgraph-device-codec-dma-capture.m4, `VA_CODEC_DMA_TX_0', VA_CODEC_DMA_TX_0,
	`S16_LE', 48000, 48000, 1, 2,
	LPAIF_INTF_TYPE_VA, CODEC_INTF_IDX_TX0, 0, DATA_FORMAT_FIXED_POINT,
	0x00004008, 0x00004008, 0x00006080)
dnl
dnl WCDTX Capture
DEVICE_SG_ADD(audioreach/subgraph-device-codec-dma-capture.m4, `TX_CODEC_DMA_TX_3', TX_CODEC_DMA_TX_3,
	`S16_LE', 48000, 48000, 1, 2,
	LPAIF_INTF_TYPE_RXTX, CODEC_INTF_IDX_TX3, 0, DATA_FORMAT_FIXED_POINT,
	0x00004009, 0x00004009, 0x00006090)
dnl
dnl Tertiary MI2S Playback - the four CS35L41 speaker amps.
DEVICE_SG_ADD(audioreach/subgraph-device-i2s-playback.m4, `Tertiary', TERTIARY_MI2S_RX,
	`S16_LE', 48000, 48000, 2, 2,
	LPAIF_INTF_TYPE_LPAIF, I2S_INTF_TYPE_TERTIARY, ZEUS_SPK_SD_LINE, DATA_FORMAT_FIXED_POINT,
	0x0000400a, 0x0000400a, 0x000060a0, `TERTIARY_MI2S_RX')

STREAM_DEVICE_PLAYBACK_MIXER(WSA_CODEC_DMA_RX_0, ``WSA_CODEC_DMA_RX_0'', ``MultiMedia1'', ``MultiMedia2'')
STREAM_DEVICE_PLAYBACK_MIXER(PRIMARY_MI2S_RX, ``PRIMARY_MI2S_RX'', ``MultiMedia1'', ``MultiMedia2'')
STREAM_DEVICE_PLAYBACK_MIXER(RX_CODEC_DMA_RX_0, ``RX_CODEC_DMA_RX_0'', ``MultiMedia1'', ``MultiMedia2'')
STREAM_DEVICE_PLAYBACK_MIXER(TERTIARY_MI2S_RX, ``TERTIARY_MI2S_RX'', ``MultiMedia1'', ``MultiMedia2'')

STREAM_DEVICE_PLAYBACK_ROUTE(WSA_CODEC_DMA_RX_0, ``WSA_CODEC_DMA_RX_0 Audio Mixer'', ``MultiMedia1, stream0.logger1'', ``MultiMedia2, stream1.logger1'')
STREAM_DEVICE_PLAYBACK_ROUTE(PRIMARY_MI2S_RX, ``PRIMARY_MI2S_RX Audio Mixer'', ``MultiMedia1, stream0.logger1'', ``MultiMedia2, stream1.logger1'')
STREAM_DEVICE_PLAYBACK_ROUTE(RX_CODEC_DMA_RX_0, ``RX_CODEC_DMA_RX_0 Audio Mixer'', ``MultiMedia1, stream0.logger1'', ``MultiMedia2, stream1.logger1'')
STREAM_DEVICE_PLAYBACK_ROUTE(TERTIARY_MI2S_RX, ``TERTIARY_MI2S_RX Audio Mixer'', ``MultiMedia1, stream0.logger1'', ``MultiMedia2, stream1.logger1'')

dnl STREAM_DEVICE_CAPTURE_MIXER(stream-index, kcontro1, kcontrol2... kcontrolN)
STREAM_DEVICE_CAPTURE_MIXER(FRONTEND_DAI_MULTIMEDIA3, ``VA_CODEC_DMA_TX_0'',``TX_CODEC_DMA_TX_3'' )
STREAM_DEVICE_CAPTURE_MIXER(FRONTEND_DAI_MULTIMEDIA4, ``VA_CODEC_DMA_TX_0'',``TX_CODEC_DMA_TX_3'' )
dnl STREAM_DEVICE_CAPTURE_ROUTE(stream-index, mixer-name, route1, route2.. routeN)
STREAM_DEVICE_CAPTURE_ROUTE(FRONTEND_DAI_MULTIMEDIA3, ``MultiMedia3 Mixer'', ``VA_CODEC_DMA_TX_0, device110.logger1'', ``TX_CODEC_DMA_TX_3, device120.logger1'')
STREAM_DEVICE_CAPTURE_ROUTE(FRONTEND_DAI_MULTIMEDIA4, ``MultiMedia4 Mixer'', ``VA_CODEC_DMA_TX_0, device110.logger1'', ``TX_CODEC_DMA_TX_3, device120.logger1'')
