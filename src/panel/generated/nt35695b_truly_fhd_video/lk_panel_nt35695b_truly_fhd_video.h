// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_NT35695B_TRULY_FHD_VIDEO_H_
#define _PANEL_NT35695B_TRULY_FHD_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config nt35695b_truly_fhd_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_nt35695b_truly_fhd_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution nt35695b_truly_fhd_video_panel_res = {
	.panel_width = 1080,
	.panel_height = 1920,
	.hfront_porch = 120,
	.hback_porch = 60,
	.hpulse_width = 12,
	.hsync_skew = 0,
	.vfront_porch = 12,
	.vback_porch = 2,
	.vpulse_width = 2,
	/* Borders not supported yet */
};

static struct color_info nt35695b_truly_fhd_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char nt35695b_truly_fhd_video_on_cmd_0[] = {
	0xff, 0x20, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_1[] = {
	0xfb, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_2[] = {
	0x00, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_3[] = {
	0x01, 0x55, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_4[] = {
	0x02, 0x45, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_5[] = {
	0x03, 0x55, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_6[] = {
	0x05, 0x50, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_7[] = {
	0x06, 0xa8, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_8[] = {
	0x07, 0xad, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_9[] = {
	0x08, 0x0c, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_10[] = {
	0x0b, 0xaa, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_11[] = {
	0x0c, 0xaa, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_12[] = {
	0x0e, 0xb0, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_13[] = {
	0x0f, 0xb3, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_14[] = {
	0x11, 0x28, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_15[] = {
	0x12, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_16[] = {
	0x13, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_17[] = {
	0x14, 0x4a, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_18[] = {
	0x15, 0x12, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_19[] = {
	0x16, 0x12, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_20[] = {
	0x30, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_21[] = {
	0x72, 0x11, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_22[] = {
	0x58, 0x82, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_23[] = {
	0x59, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_24[] = {
	0x5a, 0x02, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_25[] = {
	0x5b, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_26[] = {
	0x5c, 0x82, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_27[] = {
	0x5d, 0x80, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_28[] = {
	0x5e, 0x02, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_29[] = {
	0x5f, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_30[] = {
	0xff, 0x24, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_31[] = {
	0xfb, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_32[] = {
	0x00, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_33[] = {
	0x01, 0x0b, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_34[] = {
	0x02, 0x0c, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_35[] = {
	0x03, 0x89, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_36[] = {
	0x04, 0x8a, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_37[] = {
	0x05, 0x0f, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_38[] = {
	0x06, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_39[] = {
	0x07, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_40[] = {
	0x08, 0x1c, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_41[] = {
	0x09, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_42[] = {
	0x0a, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_43[] = {
	0x0b, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_44[] = {
	0x0c, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_45[] = {
	0x0d, 0x13, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_46[] = {
	0x0e, 0x15, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_47[] = {
	0x0f, 0x17, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_48[] = {
	0x10, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_49[] = {
	0x11, 0x0b, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_50[] = {
	0x12, 0x0c, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_51[] = {
	0x13, 0x89, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_52[] = {
	0x14, 0x8a, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_53[] = {
	0x15, 0x0f, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_54[] = {
	0x16, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_55[] = {
	0x17, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_56[] = {
	0x18, 0x1c, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_57[] = {
	0x19, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_58[] = {
	0x1a, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_59[] = {
	0x1b, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_60[] = {
	0x1c, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_61[] = {
	0x1d, 0x13, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_62[] = {
	0x1e, 0x15, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_63[] = {
	0x1f, 0x17, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_64[] = {
	0x20, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_65[] = {
	0x21, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_66[] = {
	0x22, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_67[] = {
	0x23, 0x40, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_68[] = {
	0x24, 0x40, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_69[] = {
	0x25, 0x6d, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_70[] = {
	0x26, 0x40, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_71[] = {
	0x27, 0x40, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_72[] = {
	0x29, 0xd8, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_73[] = {
	0x2a, 0x2a, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_74[] = {
	0x4b, 0x03, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_75[] = {
	0x4c, 0x11, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_76[] = {
	0x4d, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_77[] = {
	0x4e, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_78[] = {
	0x4f, 0x01, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_79[] = {
	0x50, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_80[] = {
	0x51, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_81[] = {
	0x52, 0x80, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_82[] = {
	0x53, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_83[] = {
	0x54, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_84[] = {
	0x55, 0x25, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_85[] = {
	0x56, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_86[] = {
	0x58, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_87[] = {
	0x5b, 0x43, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_88[] = {
	0x5c, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_89[] = {
	0x5f, 0x73, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_90[] = {
	0x60, 0x73, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_91[] = {
	0x63, 0x22, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_92[] = {
	0x64, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_93[] = {
	0x67, 0x08, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_94[] = {
	0x68, 0x04, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_95[] = {
	0x7a, 0x80, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_96[] = {
	0x7b, 0x91, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_97[] = {
	0x7c, 0xd8, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_98[] = {
	0x7d, 0x60, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_99[] = {
	0x93, 0x06, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_100[] = {
	0x94, 0x06, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_101[] = {
	0x8a, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_102[] = {
	0x9b, 0x0f, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_103[] = {
	0xb3, 0xc0, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_104[] = {
	0xb4, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_105[] = {
	0xb5, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_106[] = {
	0xb6, 0x21, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_107[] = {
	0xb7, 0x22, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_108[] = {
	0xb8, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_109[] = {
	0xb9, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_110[] = {
	0xba, 0x22, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_111[] = {
	0xbd, 0x20, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_112[] = {
	0xbe, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_113[] = {
	0xbf, 0x07, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_114[] = {
	0xc1, 0x6d, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_115[] = {
	0xc4, 0x24, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_116[] = {
	0xe3, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_117[] = {
	0xec, 0x00, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_118[] = {
	0xff, 0x10, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_119[] = {
	0xbb, 0x03, 0x15, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_120[] = {
	0x11, 0x00, 0x05, 0x80
};
static char nt35695b_truly_fhd_video_on_cmd_121[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd nt35695b_truly_fhd_video_on_command[] = {
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_0), nt35695b_truly_fhd_video_on_cmd_0, 16 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_1), nt35695b_truly_fhd_video_on_cmd_1, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_2), nt35695b_truly_fhd_video_on_cmd_2, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_3), nt35695b_truly_fhd_video_on_cmd_3, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_4), nt35695b_truly_fhd_video_on_cmd_4, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_5), nt35695b_truly_fhd_video_on_cmd_5, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_6), nt35695b_truly_fhd_video_on_cmd_6, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_7), nt35695b_truly_fhd_video_on_cmd_7, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_8), nt35695b_truly_fhd_video_on_cmd_8, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_9), nt35695b_truly_fhd_video_on_cmd_9, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_10), nt35695b_truly_fhd_video_on_cmd_10, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_11), nt35695b_truly_fhd_video_on_cmd_11, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_12), nt35695b_truly_fhd_video_on_cmd_12, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_13), nt35695b_truly_fhd_video_on_cmd_13, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_14), nt35695b_truly_fhd_video_on_cmd_14, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_15), nt35695b_truly_fhd_video_on_cmd_15, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_16), nt35695b_truly_fhd_video_on_cmd_16, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_17), nt35695b_truly_fhd_video_on_cmd_17, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_18), nt35695b_truly_fhd_video_on_cmd_18, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_19), nt35695b_truly_fhd_video_on_cmd_19, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_20), nt35695b_truly_fhd_video_on_cmd_20, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_21), nt35695b_truly_fhd_video_on_cmd_21, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_22), nt35695b_truly_fhd_video_on_cmd_22, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_23), nt35695b_truly_fhd_video_on_cmd_23, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_24), nt35695b_truly_fhd_video_on_cmd_24, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_25), nt35695b_truly_fhd_video_on_cmd_25, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_26), nt35695b_truly_fhd_video_on_cmd_26, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_27), nt35695b_truly_fhd_video_on_cmd_27, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_28), nt35695b_truly_fhd_video_on_cmd_28, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_29), nt35695b_truly_fhd_video_on_cmd_29, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_30), nt35695b_truly_fhd_video_on_cmd_30, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_31), nt35695b_truly_fhd_video_on_cmd_31, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_32), nt35695b_truly_fhd_video_on_cmd_32, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_33), nt35695b_truly_fhd_video_on_cmd_33, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_34), nt35695b_truly_fhd_video_on_cmd_34, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_35), nt35695b_truly_fhd_video_on_cmd_35, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_36), nt35695b_truly_fhd_video_on_cmd_36, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_37), nt35695b_truly_fhd_video_on_cmd_37, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_38), nt35695b_truly_fhd_video_on_cmd_38, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_39), nt35695b_truly_fhd_video_on_cmd_39, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_40), nt35695b_truly_fhd_video_on_cmd_40, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_41), nt35695b_truly_fhd_video_on_cmd_41, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_42), nt35695b_truly_fhd_video_on_cmd_42, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_43), nt35695b_truly_fhd_video_on_cmd_43, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_44), nt35695b_truly_fhd_video_on_cmd_44, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_45), nt35695b_truly_fhd_video_on_cmd_45, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_46), nt35695b_truly_fhd_video_on_cmd_46, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_47), nt35695b_truly_fhd_video_on_cmd_47, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_48), nt35695b_truly_fhd_video_on_cmd_48, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_49), nt35695b_truly_fhd_video_on_cmd_49, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_50), nt35695b_truly_fhd_video_on_cmd_50, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_51), nt35695b_truly_fhd_video_on_cmd_51, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_52), nt35695b_truly_fhd_video_on_cmd_52, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_53), nt35695b_truly_fhd_video_on_cmd_53, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_54), nt35695b_truly_fhd_video_on_cmd_54, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_55), nt35695b_truly_fhd_video_on_cmd_55, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_56), nt35695b_truly_fhd_video_on_cmd_56, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_57), nt35695b_truly_fhd_video_on_cmd_57, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_58), nt35695b_truly_fhd_video_on_cmd_58, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_59), nt35695b_truly_fhd_video_on_cmd_59, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_60), nt35695b_truly_fhd_video_on_cmd_60, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_61), nt35695b_truly_fhd_video_on_cmd_61, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_62), nt35695b_truly_fhd_video_on_cmd_62, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_63), nt35695b_truly_fhd_video_on_cmd_63, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_64), nt35695b_truly_fhd_video_on_cmd_64, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_65), nt35695b_truly_fhd_video_on_cmd_65, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_66), nt35695b_truly_fhd_video_on_cmd_66, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_67), nt35695b_truly_fhd_video_on_cmd_67, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_68), nt35695b_truly_fhd_video_on_cmd_68, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_69), nt35695b_truly_fhd_video_on_cmd_69, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_70), nt35695b_truly_fhd_video_on_cmd_70, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_71), nt35695b_truly_fhd_video_on_cmd_71, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_72), nt35695b_truly_fhd_video_on_cmd_72, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_73), nt35695b_truly_fhd_video_on_cmd_73, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_74), nt35695b_truly_fhd_video_on_cmd_74, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_75), nt35695b_truly_fhd_video_on_cmd_75, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_76), nt35695b_truly_fhd_video_on_cmd_76, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_77), nt35695b_truly_fhd_video_on_cmd_77, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_78), nt35695b_truly_fhd_video_on_cmd_78, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_79), nt35695b_truly_fhd_video_on_cmd_79, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_80), nt35695b_truly_fhd_video_on_cmd_80, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_81), nt35695b_truly_fhd_video_on_cmd_81, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_82), nt35695b_truly_fhd_video_on_cmd_82, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_83), nt35695b_truly_fhd_video_on_cmd_83, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_84), nt35695b_truly_fhd_video_on_cmd_84, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_85), nt35695b_truly_fhd_video_on_cmd_85, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_86), nt35695b_truly_fhd_video_on_cmd_86, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_87), nt35695b_truly_fhd_video_on_cmd_87, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_88), nt35695b_truly_fhd_video_on_cmd_88, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_89), nt35695b_truly_fhd_video_on_cmd_89, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_90), nt35695b_truly_fhd_video_on_cmd_90, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_91), nt35695b_truly_fhd_video_on_cmd_91, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_92), nt35695b_truly_fhd_video_on_cmd_92, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_93), nt35695b_truly_fhd_video_on_cmd_93, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_94), nt35695b_truly_fhd_video_on_cmd_94, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_95), nt35695b_truly_fhd_video_on_cmd_95, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_96), nt35695b_truly_fhd_video_on_cmd_96, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_97), nt35695b_truly_fhd_video_on_cmd_97, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_98), nt35695b_truly_fhd_video_on_cmd_98, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_99), nt35695b_truly_fhd_video_on_cmd_99, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_100), nt35695b_truly_fhd_video_on_cmd_100, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_101), nt35695b_truly_fhd_video_on_cmd_101, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_102), nt35695b_truly_fhd_video_on_cmd_102, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_103), nt35695b_truly_fhd_video_on_cmd_103, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_104), nt35695b_truly_fhd_video_on_cmd_104, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_105), nt35695b_truly_fhd_video_on_cmd_105, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_106), nt35695b_truly_fhd_video_on_cmd_106, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_107), nt35695b_truly_fhd_video_on_cmd_107, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_108), nt35695b_truly_fhd_video_on_cmd_108, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_109), nt35695b_truly_fhd_video_on_cmd_109, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_110), nt35695b_truly_fhd_video_on_cmd_110, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_111), nt35695b_truly_fhd_video_on_cmd_111, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_112), nt35695b_truly_fhd_video_on_cmd_112, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_113), nt35695b_truly_fhd_video_on_cmd_113, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_114), nt35695b_truly_fhd_video_on_cmd_114, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_115), nt35695b_truly_fhd_video_on_cmd_115, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_116), nt35695b_truly_fhd_video_on_cmd_116, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_117), nt35695b_truly_fhd_video_on_cmd_117, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_118), nt35695b_truly_fhd_video_on_cmd_118, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_119), nt35695b_truly_fhd_video_on_cmd_119, 0 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_120), nt35695b_truly_fhd_video_on_cmd_120, 120 },
	{ sizeof(nt35695b_truly_fhd_video_on_cmd_121), nt35695b_truly_fhd_video_on_cmd_121, 120 },
};

static char nt35695b_truly_fhd_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char nt35695b_truly_fhd_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd nt35695b_truly_fhd_video_off_command[] = {
	{ sizeof(nt35695b_truly_fhd_video_off_cmd_0), nt35695b_truly_fhd_video_off_cmd_0, 20 },
	{ sizeof(nt35695b_truly_fhd_video_off_cmd_1), nt35695b_truly_fhd_video_off_cmd_1, 120 },
};

static struct command_state nt35695b_truly_fhd_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 0,
};

static struct commandpanel_info nt35695b_truly_fhd_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info nt35695b_truly_fhd_video_video_panel = {
	.hsync_pulse = 0,
	.hfp_power_mode = 0,
	.hbp_power_mode = 0,
	.hsa_power_mode = 0,
	.bllp_eof_power_mode = 1,
	.bllp_power_mode = 1,
	.traffic_mode = 2,
	/* This is bllp_eof_power_mode and bllp_power_mode combined */
	.bllp_eof_power = 1 << 3 | 1 << 0,
};

static struct lane_configuration nt35695b_truly_fhd_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t nt35695b_truly_fhd_video_timings[] = {
	
};

static struct panel_timing nt35695b_truly_fhd_video_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence nt35695b_truly_fhd_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static inline void panel_nt35695b_truly_fhd_video_select(struct panel_struct *panel,
							 struct msm_panel_info *pinfo,
							 struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &nt35695b_truly_fhd_video_panel_data;
	panel->panelres = &nt35695b_truly_fhd_video_panel_res;
	panel->color = &nt35695b_truly_fhd_video_color;
	panel->videopanel = &nt35695b_truly_fhd_video_video_panel;
	panel->commandpanel = &nt35695b_truly_fhd_video_command_panel;
	panel->state = &nt35695b_truly_fhd_video_state;
	panel->laneconfig = &nt35695b_truly_fhd_video_lane_config;
	panel->paneltiminginfo = &nt35695b_truly_fhd_video_timing_info;
	panel->panelresetseq = &nt35695b_truly_fhd_video_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = nt35695b_truly_fhd_video_on_command;
	pinfo->mipi.panel_off_cmds = nt35695b_truly_fhd_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(nt35695b_truly_fhd_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(nt35695b_truly_fhd_video_off_command);
	memcpy(phy_db->timing, nt35695b_truly_fhd_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_NT35695B_TRULY_FHD_VIDEO_H_ */
