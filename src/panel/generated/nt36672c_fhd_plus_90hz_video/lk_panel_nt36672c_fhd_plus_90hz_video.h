// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_NT36672C_FHD_PLUS_90HZ_VIDEO_H_
#define _PANEL_NT36672C_FHD_PLUS_90HZ_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config nt36672c_fhd_plus_90hz_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_nt36672c_fhd_plus_90hz_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 90,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution nt36672c_fhd_plus_90hz_video_panel_res = {
	.panel_width = 1080,
	.panel_height = 2400,
	.hfront_porch = 76,
	.hback_porch = 80,
	.hpulse_width = 12,
	.hsync_skew = 0,
	.vfront_porch = 54,
	.vback_porch = 10,
	.vpulse_width = 10,
	/* Borders not supported yet */
};

static struct color_info nt36672c_fhd_plus_90hz_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char nt36672c_fhd_plus_90hz_video_on_cmd_0[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_1[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_2[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_3[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_4[] = {
	0x03, 0x00, 0x39, 0xc0, 0xc2, 0x1b, 0xa0, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_5[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x20, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_6[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_7[] = {
	0x02, 0x00, 0x39, 0xc0, 0x01, 0x66, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_8[] = {
	0x02, 0x00, 0x39, 0xc0, 0x06, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_9[] = {
	0x02, 0x00, 0x39, 0xc0, 0x07, 0x38, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_10[] = {
	0x02, 0x00, 0x39, 0xc0, 0x18, 0x66, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_11[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1b, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_12[] = {
	0x02, 0x00, 0x39, 0xc0, 0x5c, 0x90, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_13[] = {
	0x02, 0x00, 0x39, 0xc0, 0x5e, 0xaa, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_14[] = {
	0x02, 0x00, 0x39, 0xc0, 0x69, 0x91, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_15[] = {
	0x02, 0x00, 0x39, 0xc0, 0x89, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_16[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8a, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_17[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8d, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_18[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8e, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_19[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8f, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_20[] = {
	0x02, 0x00, 0x39, 0xc0, 0x91, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_21[] = {
	0x02, 0x00, 0x39, 0xc0, 0x95, 0xd1, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_22[] = {
	0x02, 0x00, 0x39, 0xc0, 0x96, 0xd1, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_23[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf2, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_24[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf3, 0x64, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_25[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf4, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_26[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf5, 0x64, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_27[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf6, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_28[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf7, 0x64, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_29[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf8, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_30[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf9, 0x64, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_31[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x24, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_32[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_33[] = {
	0x02, 0x00, 0x39, 0xc0, 0x01, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_34[] = {
	0x02, 0x00, 0x39, 0xc0, 0x03, 0x0c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_35[] = {
	0x02, 0x00, 0x39, 0xc0, 0x05, 0x1d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_36[] = {
	0x02, 0x00, 0x39, 0xc0, 0x08, 0x2f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_37[] = {
	0x02, 0x00, 0x39, 0xc0, 0x09, 0x2e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_38[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0a, 0x2d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_39[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0b, 0x2c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_40[] = {
	0x02, 0x00, 0x39, 0xc0, 0x11, 0x17, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_41[] = {
	0x02, 0x00, 0x39, 0xc0, 0x12, 0x13, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_42[] = {
	0x02, 0x00, 0x39, 0xc0, 0x13, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_43[] = {
	0x02, 0x00, 0x39, 0xc0, 0x15, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_44[] = {
	0x02, 0x00, 0x39, 0xc0, 0x16, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_45[] = {
	0x02, 0x00, 0x39, 0xc0, 0x17, 0x18, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_46[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1b, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_47[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1d, 0x1d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_48[] = {
	0x02, 0x00, 0x39, 0xc0, 0x20, 0x2f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_49[] = {
	0x02, 0x00, 0x39, 0xc0, 0x21, 0x2e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_50[] = {
	0x02, 0x00, 0x39, 0xc0, 0x22, 0x2d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_51[] = {
	0x02, 0x00, 0x39, 0xc0, 0x23, 0x2c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_52[] = {
	0x02, 0x00, 0x39, 0xc0, 0x29, 0x17, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_53[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2a, 0x13, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_54[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2b, 0x15, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_55[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2f, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_56[] = {
	0x02, 0x00, 0x39, 0xc0, 0x30, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_57[] = {
	0x02, 0x00, 0x39, 0xc0, 0x31, 0x18, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_58[] = {
	0x02, 0x00, 0x39, 0xc0, 0x32, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_59[] = {
	0x02, 0x00, 0x39, 0xc0, 0x34, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_60[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_61[] = {
	0x02, 0x00, 0x39, 0xc0, 0x36, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_62[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4d, 0x19, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_63[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4e, 0x45, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_64[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4f, 0x45, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_65[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x45, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_66[] = {
	0x02, 0x00, 0x39, 0xc0, 0x71, 0x30, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_67[] = {
	0x02, 0x00, 0x39, 0xc0, 0x79, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_68[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7a, 0x82, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_69[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7b, 0x94, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_70[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7d, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_71[] = {
	0x02, 0x00, 0x39, 0xc0, 0x80, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_72[] = {
	0x02, 0x00, 0x39, 0xc0, 0x81, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_73[] = {
	0x02, 0x00, 0x39, 0xc0, 0x82, 0x13, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_74[] = {
	0x02, 0x00, 0x39, 0xc0, 0x84, 0x31, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_75[] = {
	0x02, 0x00, 0x39, 0xc0, 0x85, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_76[] = {
	0x02, 0x00, 0x39, 0xc0, 0x86, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_77[] = {
	0x02, 0x00, 0x39, 0xc0, 0x87, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_78[] = {
	0x02, 0x00, 0x39, 0xc0, 0x90, 0x13, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_79[] = {
	0x02, 0x00, 0x39, 0xc0, 0x92, 0x31, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_80[] = {
	0x02, 0x00, 0x39, 0xc0, 0x93, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_81[] = {
	0x02, 0x00, 0x39, 0xc0, 0x94, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_82[] = {
	0x02, 0x00, 0x39, 0xc0, 0x95, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_83[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9c, 0xf4, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_84[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9d, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_85[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa0, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_86[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa2, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_87[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa3, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_88[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa4, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_89[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa5, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_90[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc4, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_91[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc6, 0xc0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_92[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc9, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_93[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd9, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_94[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe9, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_95[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x25, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_96[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_97[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0f, 0x1b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_98[] = {
	0x02, 0x00, 0x39, 0xc0, 0x19, 0xe4, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_99[] = {
	0x02, 0x00, 0x39, 0xc0, 0x21, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_100[] = {
	0x02, 0x00, 0x39, 0xc0, 0x66, 0xd8, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_101[] = {
	0x02, 0x00, 0x39, 0xc0, 0x68, 0x50, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_102[] = {
	0x02, 0x00, 0x39, 0xc0, 0x69, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_103[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6b, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_104[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6d, 0x0d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_105[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6e, 0x48, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_106[] = {
	0x02, 0x00, 0x39, 0xc0, 0x72, 0x41, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_107[] = {
	0x02, 0x00, 0x39, 0xc0, 0x73, 0x4a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_108[] = {
	0x02, 0x00, 0x39, 0xc0, 0x74, 0xd0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_109[] = {
	0x02, 0x00, 0x39, 0xc0, 0x77, 0x62, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_110[] = {
	0x02, 0x00, 0x39, 0xc0, 0x79, 0x7f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_111[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7d, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_112[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7f, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_113[] = {
	0x02, 0x00, 0x39, 0xc0, 0x80, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_114[] = {
	0x02, 0x00, 0x39, 0xc0, 0x84, 0x0d, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_115[] = {
	0x02, 0x00, 0x39, 0xc0, 0xcf, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_116[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd6, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_117[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd7, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_118[] = {
	0x02, 0x00, 0x39, 0xc0, 0xef, 0x20, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_119[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf0, 0x84, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_120[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x26, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_121[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_122[] = {
	0x02, 0x00, 0x39, 0xc0, 0x15, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_123[] = {
	0x02, 0x00, 0x39, 0xc0, 0x81, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_124[] = {
	0x02, 0x00, 0x39, 0xc0, 0x83, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_125[] = {
	0x02, 0x00, 0x39, 0xc0, 0x84, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_126[] = {
	0x02, 0x00, 0x39, 0xc0, 0x85, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_127[] = {
	0x02, 0x00, 0x39, 0xc0, 0x86, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_128[] = {
	0x02, 0x00, 0x39, 0xc0, 0x87, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_129[] = {
	0x02, 0x00, 0x39, 0xc0, 0x88, 0x06, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_130[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8a, 0x1a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_131[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8b, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_132[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8c, 0x24, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_133[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8e, 0x42, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_134[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8f, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_135[] = {
	0x02, 0x00, 0x39, 0xc0, 0x90, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_136[] = {
	0x02, 0x00, 0x39, 0xc0, 0x91, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_137[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9a, 0x81, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_138[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9b, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_139[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9c, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_140[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9d, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_141[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9e, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_142[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x27, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_143[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_144[] = {
	0x02, 0x00, 0x39, 0xc0, 0x01, 0x60, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_145[] = {
	0x02, 0x00, 0x39, 0xc0, 0x20, 0x81, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_146[] = {
	0x02, 0x00, 0x39, 0xc0, 0x21, 0xea, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_147[] = {
	0x02, 0x00, 0x39, 0xc0, 0x25, 0x82, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_148[] = {
	0x02, 0x00, 0x39, 0xc0, 0x26, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_149[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6e, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_150[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6f, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_151[] = {
	0x02, 0x00, 0x39, 0xc0, 0x70, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_152[] = {
	0x02, 0x00, 0x39, 0xc0, 0x71, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_153[] = {
	0x02, 0x00, 0x39, 0xc0, 0x72, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_154[] = {
	0x02, 0x00, 0x39, 0xc0, 0x75, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_155[] = {
	0x02, 0x00, 0x39, 0xc0, 0x76, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_156[] = {
	0x02, 0x00, 0x39, 0xc0, 0x77, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_157[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7d, 0x09, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_158[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7e, 0x5f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_159[] = {
	0x02, 0x00, 0x39, 0xc0, 0x80, 0x23, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_160[] = {
	0x02, 0x00, 0x39, 0xc0, 0x82, 0x09, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_161[] = {
	0x02, 0x00, 0x39, 0xc0, 0x83, 0x5f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_162[] = {
	0x02, 0x00, 0x39, 0xc0, 0x88, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_163[] = {
	0x02, 0x00, 0x39, 0xc0, 0x89, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_164[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa5, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_165[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa6, 0x23, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_166[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa7, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_167[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb6, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_168[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe3, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_169[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe4, 0xe0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_170[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe5, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_171[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe6, 0x70, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_172[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe9, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_173[] = {
	0x02, 0x00, 0x39, 0xc0, 0xea, 0x2f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_174[] = {
	0x02, 0x00, 0x39, 0xc0, 0xeb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_175[] = {
	0x02, 0x00, 0x39, 0xc0, 0xec, 0x98, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_176[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x2a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_177[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_178[] = {
	0x02, 0x00, 0x39, 0xc0, 0x00, 0x91, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_179[] = {
	0x02, 0x00, 0x39, 0xc0, 0x03, 0x20, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_180[] = {
	0x02, 0x00, 0x39, 0xc0, 0x07, 0x5a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_181[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0a, 0x70, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_182[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0d, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_183[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0e, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_184[] = {
	0x02, 0x00, 0x39, 0xc0, 0x11, 0xf0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_185[] = {
	0x02, 0x00, 0x39, 0xc0, 0x15, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_186[] = {
	0x02, 0x00, 0x39, 0xc0, 0x16, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_187[] = {
	0x02, 0x00, 0x39, 0xc0, 0x19, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_188[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1a, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_189[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1b, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_190[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1d, 0x36, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_191[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1e, 0x4f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_192[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1f, 0x4f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_193[] = {
	0x02, 0x00, 0x39, 0xc0, 0x20, 0x4f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_194[] = {
	0x02, 0x00, 0x39, 0xc0, 0x28, 0xe4, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_195[] = {
	0x02, 0x00, 0x39, 0xc0, 0x29, 0x17, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_196[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2a, 0xf5, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_197[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2d, 0x06, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_198[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2f, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_199[] = {
	0x02, 0x00, 0x39, 0xc0, 0x30, 0x54, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_200[] = {
	0x02, 0x00, 0x39, 0xc0, 0x33, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_201[] = {
	0x02, 0x00, 0x39, 0xc0, 0x34, 0xe6, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_202[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x32, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_203[] = {
	0x02, 0x00, 0x39, 0xc0, 0x36, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_204[] = {
	0x02, 0x00, 0x39, 0xc0, 0x37, 0xe1, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_205[] = {
	0x02, 0x00, 0x39, 0xc0, 0x38, 0x36, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_206[] = {
	0x02, 0x00, 0x39, 0xc0, 0x39, 0xfe, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_207[] = {
	0x02, 0x00, 0x39, 0xc0, 0x3a, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_208[] = {
	0x02, 0x00, 0x39, 0xc0, 0x46, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_209[] = {
	0x02, 0x00, 0x39, 0xc0, 0x47, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_210[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4a, 0xf0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_211[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4e, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_212[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4f, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_213[] = {
	0x02, 0x00, 0x39, 0xc0, 0x52, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_214[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_215[] = {
	0x02, 0x00, 0x39, 0xc0, 0x54, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_216[] = {
	0x02, 0x00, 0x39, 0xc0, 0x56, 0x36, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_217[] = {
	0x02, 0x00, 0x39, 0xc0, 0x57, 0x7e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_218[] = {
	0x02, 0x00, 0x39, 0xc0, 0x58, 0x7e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_219[] = {
	0x02, 0x00, 0x39, 0xc0, 0x59, 0x7e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_220[] = {
	0x02, 0x00, 0x39, 0xc0, 0x60, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_221[] = {
	0x02, 0x00, 0x39, 0xc0, 0x61, 0xc9, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_222[] = {
	0x02, 0x00, 0x39, 0xc0, 0x62, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_223[] = {
	0x02, 0x00, 0x39, 0xc0, 0x63, 0xfb, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_224[] = {
	0x02, 0x00, 0x39, 0xc0, 0x64, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_225[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x05, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_226[] = {
	0x02, 0x00, 0x39, 0xc0, 0x66, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_227[] = {
	0x02, 0x00, 0x39, 0xc0, 0x67, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_228[] = {
	0x02, 0x00, 0x39, 0xc0, 0x68, 0x91, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_229[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6a, 0x19, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_230[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6b, 0xcb, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_231[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6c, 0x20, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_232[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6d, 0xe5, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_233[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6e, 0xc8, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_234[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6f, 0x22, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_235[] = {
	0x02, 0x00, 0x39, 0xc0, 0x70, 0xe3, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_236[] = {
	0x02, 0x00, 0x39, 0xc0, 0x71, 0x04, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_237[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7a, 0x07, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_238[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7b, 0x40, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_239[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7d, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_240[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7f, 0x2c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_241[] = {
	0x02, 0x00, 0x39, 0xc0, 0x83, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_242[] = {
	0x02, 0x00, 0x39, 0xc0, 0x84, 0x65, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_243[] = {
	0x02, 0x00, 0x39, 0xc0, 0x87, 0x0f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_244[] = {
	0x02, 0x00, 0x39, 0xc0, 0x88, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_245[] = {
	0x02, 0x00, 0x39, 0xc0, 0x89, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_246[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8b, 0x36, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_247[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8c, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_248[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8d, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_249[] = {
	0x02, 0x00, 0x39, 0xc0, 0x8e, 0x39, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_250[] = {
	0x02, 0x00, 0x39, 0xc0, 0x95, 0x80, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_251[] = {
	0x02, 0x00, 0x39, 0xc0, 0x96, 0xfd, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_252[] = {
	0x02, 0x00, 0x39, 0xc0, 0x97, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_253[] = {
	0x02, 0x00, 0x39, 0xc0, 0x98, 0xb3, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_254[] = {
	0x02, 0x00, 0x39, 0xc0, 0x99, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_255[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9a, 0x08, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_256[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9b, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_257[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9c, 0x4c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_258[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9d, 0xbc, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_259[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9f, 0xac, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_260[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa0, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_261[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa2, 0x44, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_262[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa3, 0x78, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_263[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa4, 0xf8, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_264[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa5, 0x4a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_265[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa6, 0x72, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_266[] = {
	0x02, 0x00, 0x39, 0xc0, 0xa7, 0x4c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_267[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x2c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_268[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_269[] = {
	0x02, 0x00, 0x39, 0xc0, 0x00, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_270[] = {
	0x02, 0x00, 0x39, 0xc0, 0x01, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_271[] = {
	0x02, 0x00, 0x39, 0xc0, 0x02, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_272[] = {
	0x02, 0x00, 0x39, 0xc0, 0x03, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_273[] = {
	0x02, 0x00, 0x39, 0xc0, 0x04, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_274[] = {
	0x02, 0x00, 0x39, 0xc0, 0x05, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_275[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0d, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_276[] = {
	0x02, 0x00, 0x39, 0xc0, 0x0e, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_277[] = {
	0x02, 0x00, 0x39, 0xc0, 0x16, 0x1b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_278[] = {
	0x02, 0x00, 0x39, 0xc0, 0x17, 0x4b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_279[] = {
	0x02, 0x00, 0x39, 0xc0, 0x18, 0x4b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_280[] = {
	0x02, 0x00, 0x39, 0xc0, 0x19, 0x4b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_281[] = {
	0x02, 0x00, 0x39, 0xc0, 0x2a, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_282[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4d, 0x16, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_283[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4e, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_284[] = {
	0x02, 0x00, 0x39, 0xc0, 0x4f, 0x2f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_285[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_286[] = {
	0x02, 0x00, 0x39, 0xc0, 0x54, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_287[] = {
	0x02, 0x00, 0x39, 0xc0, 0x55, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_288[] = {
	0x02, 0x00, 0x39, 0xc0, 0x56, 0x0e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_289[] = {
	0x02, 0x00, 0x39, 0xc0, 0x58, 0x0e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_290[] = {
	0x02, 0x00, 0x39, 0xc0, 0x59, 0x0e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_291[] = {
	0x02, 0x00, 0x39, 0xc0, 0x61, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_292[] = {
	0x02, 0x00, 0x39, 0xc0, 0x62, 0x1f, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_293[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6a, 0x14, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_294[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6b, 0x34, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_295[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6c, 0x34, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_296[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6d, 0x34, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_297[] = {
	0x02, 0x00, 0x39, 0xc0, 0x7e, 0x03, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_298[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9d, 0x0e, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_299[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9e, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_300[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9f, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_301[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0xe0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_302[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_303[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x20, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_304[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_305[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0x00, 0x00,
	0x15, 0x00, 0x3f, 0x00, 0x5f, 0x00, 0x7e, 0x00,
	0x97, 0x00, 0xaf, 0x00, 0xc3, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_306[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb1, 0x00, 0xd7, 0x01,
	0x0a, 0x01, 0x32, 0x01, 0x6f, 0x01, 0x9e, 0x01,
	0xe5, 0x02, 0x1d, 0x02, 0x1e, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_307[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb2, 0x02, 0x56, 0x02,
	0x94, 0x02, 0xbc, 0x02, 0xf1, 0x03, 0x13, 0x03,
	0x41, 0x03, 0x4f, 0x03, 0x5f, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_308[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xb3, 0x03, 0x71, 0x03,
	0x84, 0x03, 0x99, 0x03, 0xb0, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_309[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb4, 0x00, 0x00, 0x00,
	0x17, 0x00, 0x46, 0x00, 0x69, 0x00, 0x8c, 0x00,
	0xa5, 0x00, 0xbe, 0x00, 0xd1, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_310[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb5, 0x00, 0xe4, 0x01,
	0x18, 0x01, 0x40, 0x01, 0x7c, 0x01, 0xaa, 0x01,
	0xf0, 0x02, 0x27, 0x02, 0x28, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_311[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb6, 0x02, 0x5e, 0x02,
	0x9b, 0x02, 0xc3, 0x02, 0xf6, 0x03, 0x18, 0x03,
	0x45, 0x03, 0x54, 0x03, 0x63, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_312[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xb7, 0x03, 0x75, 0x03,
	0x87, 0x03, 0x9c, 0x03, 0xb2, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_313[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb8, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x49, 0x00, 0x6b, 0x00, 0x8e, 0x00,
	0xa8, 0x00, 0xc1, 0x00, 0xd3, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_314[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb9, 0x00, 0xe5, 0x01,
	0x18, 0x01, 0x3f, 0x01, 0x7b, 0x01, 0xa8, 0x01,
	0xec, 0x02, 0x24, 0x02, 0x26, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_315[] = {
	0x11, 0x00, 0x39, 0xc0, 0xba, 0x02, 0x5a, 0x02,
	0x97, 0x02, 0xc0, 0x02, 0xf4, 0x03, 0x15, 0x03,
	0x43, 0x03, 0x51, 0x03, 0x61, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_316[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xbb, 0x03, 0x72, 0x03,
	0x85, 0x03, 0x9a, 0x03, 0xb1, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_317[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc6, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_318[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc7, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_319[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc8, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_320[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc9, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_321[] = {
	0x02, 0x00, 0x39, 0xc0, 0xca, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_322[] = {
	0x02, 0x00, 0x39, 0xc0, 0xcb, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_323[] = {
	0x02, 0x00, 0x39, 0xc0, 0xcc, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_324[] = {
	0x02, 0x00, 0x39, 0xc0, 0xcd, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_325[] = {
	0x02, 0x00, 0x39, 0xc0, 0xce, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_326[] = {
	0x02, 0x00, 0x39, 0xc0, 0xcf, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_327[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_328[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd1, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_329[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd2, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_330[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd3, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_331[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd4, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_332[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd5, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_333[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd6, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_334[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd7, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_335[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd8, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_336[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd9, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_337[] = {
	0x02, 0x00, 0x39, 0xc0, 0xda, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_338[] = {
	0x02, 0x00, 0x39, 0xc0, 0xdb, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_339[] = {
	0x02, 0x00, 0x39, 0xc0, 0xdc, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_340[] = {
	0x02, 0x00, 0x39, 0xc0, 0xdd, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_341[] = {
	0x02, 0x00, 0x39, 0xc0, 0xde, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_342[] = {
	0x02, 0x00, 0x39, 0xc0, 0xdf, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_343[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_344[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe1, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_345[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe2, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_346[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe3, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_347[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe4, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_348[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe5, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_349[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe6, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_350[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe7, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_351[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe8, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_352[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe9, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_353[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x21, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_354[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_355[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0x00, 0x00,
	0x15, 0x00, 0x3f, 0x00, 0x5f, 0x00, 0x7e, 0x00,
	0x97, 0x00, 0xaf, 0x00, 0xc3, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_356[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb1, 0x00, 0xd7, 0x01,
	0x0a, 0x01, 0x32, 0x01, 0x6f, 0x01, 0x9e, 0x01,
	0xe5, 0x02, 0x1d, 0x02, 0x1e, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_357[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb2, 0x02, 0x56, 0x02,
	0x94, 0x02, 0xbc, 0x02, 0xf1, 0x03, 0x13, 0x03,
	0x41, 0x03, 0x4f, 0x03, 0x5f, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_358[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xb3, 0x03, 0x71, 0x03,
	0x84, 0x03, 0x99, 0x03, 0xb0, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_359[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb4, 0x00, 0x00, 0x00,
	0x17, 0x00, 0x46, 0x00, 0x69, 0x00, 0x8c, 0x00,
	0xa5, 0x00, 0xbe, 0x00, 0xd1, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_360[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb5, 0x00, 0xe4, 0x01,
	0x18, 0x01, 0x40, 0x01, 0x7c, 0x01, 0xaa, 0x01,
	0xf0, 0x02, 0x27, 0x02, 0x28, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_361[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb6, 0x02, 0x5e, 0x02,
	0x9b, 0x02, 0xc3, 0x02, 0xf6, 0x03, 0x18, 0x03,
	0x45, 0x03, 0x54, 0x03, 0x63, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_362[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xb7, 0x03, 0x75, 0x03,
	0x87, 0x03, 0x9c, 0x03, 0xb2, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_363[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb8, 0x00, 0x00, 0x00,
	0x18, 0x00, 0x49, 0x00, 0x6b, 0x00, 0x8e, 0x00,
	0xa8, 0x00, 0xc1, 0x00, 0xd3, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_364[] = {
	0x11, 0x00, 0x39, 0xc0, 0xb9, 0x00, 0xe5, 0x01,
	0x18, 0x01, 0x3f, 0x01, 0x7b, 0x01, 0xa8, 0x01,
	0xec, 0x02, 0x24, 0x02, 0x26, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_365[] = {
	0x11, 0x00, 0x39, 0xc0, 0xba, 0x02, 0x5a, 0x02,
	0x97, 0x02, 0xc0, 0x02, 0xf4, 0x03, 0x15, 0x03,
	0x43, 0x03, 0x51, 0x03, 0x61, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_366[] = {
	0x0f, 0x00, 0x39, 0xc0, 0xbb, 0x03, 0x72, 0x03,
	0x85, 0x03, 0x9a, 0x03, 0xb1, 0x03, 0xca, 0x03,
	0xd7, 0x00, 0x00, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_367[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_368[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_369[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_370[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc0, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_371[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0xf0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_372[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_373[] = {
	0x02, 0x00, 0x39, 0xc0, 0x1c, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_374[] = {
	0x02, 0x00, 0x39, 0xc0, 0x33, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_375[] = {
	0x02, 0x00, 0x39, 0xc0, 0x5a, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_376[] = {
	0x02, 0x00, 0x39, 0xc0, 0xd2, 0x52, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_377[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0xd0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_378[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_379[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x22, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_380[] = {
	0x02, 0x00, 0x39, 0xc0, 0x54, 0x02, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_381[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0xc0, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_382[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_383[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9c, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_384[] = {
	0x02, 0x00, 0x39, 0xc0, 0x9d, 0x11, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_385[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x2b, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_386[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfb, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_387[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb7, 0x0a, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_388[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb8, 0x1c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_389[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc0, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_390[] = {
	0x02, 0x00, 0x39, 0xc0, 0xff, 0x10, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_391[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x01, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_392[] = {
	0x02, 0x00, 0x39, 0xc0, 0x51, 0xff, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_393[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x0c, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_394[] = {
	0x02, 0x00, 0x39, 0xc0, 0x55, 0x00, 0xff, 0xff
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_395[] = {
	0x11, 0x00, 0x05, 0x80
};
static char nt36672c_fhd_plus_90hz_video_on_cmd_396[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd nt36672c_fhd_plus_90hz_video_on_command[] = {
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_0), nt36672c_fhd_plus_90hz_video_on_cmd_0, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_1), nt36672c_fhd_plus_90hz_video_on_cmd_1, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_2), nt36672c_fhd_plus_90hz_video_on_cmd_2, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_3), nt36672c_fhd_plus_90hz_video_on_cmd_3, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_4), nt36672c_fhd_plus_90hz_video_on_cmd_4, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_5), nt36672c_fhd_plus_90hz_video_on_cmd_5, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_6), nt36672c_fhd_plus_90hz_video_on_cmd_6, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_7), nt36672c_fhd_plus_90hz_video_on_cmd_7, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_8), nt36672c_fhd_plus_90hz_video_on_cmd_8, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_9), nt36672c_fhd_plus_90hz_video_on_cmd_9, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_10), nt36672c_fhd_plus_90hz_video_on_cmd_10, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_11), nt36672c_fhd_plus_90hz_video_on_cmd_11, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_12), nt36672c_fhd_plus_90hz_video_on_cmd_12, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_13), nt36672c_fhd_plus_90hz_video_on_cmd_13, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_14), nt36672c_fhd_plus_90hz_video_on_cmd_14, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_15), nt36672c_fhd_plus_90hz_video_on_cmd_15, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_16), nt36672c_fhd_plus_90hz_video_on_cmd_16, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_17), nt36672c_fhd_plus_90hz_video_on_cmd_17, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_18), nt36672c_fhd_plus_90hz_video_on_cmd_18, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_19), nt36672c_fhd_plus_90hz_video_on_cmd_19, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_20), nt36672c_fhd_plus_90hz_video_on_cmd_20, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_21), nt36672c_fhd_plus_90hz_video_on_cmd_21, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_22), nt36672c_fhd_plus_90hz_video_on_cmd_22, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_23), nt36672c_fhd_plus_90hz_video_on_cmd_23, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_24), nt36672c_fhd_plus_90hz_video_on_cmd_24, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_25), nt36672c_fhd_plus_90hz_video_on_cmd_25, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_26), nt36672c_fhd_plus_90hz_video_on_cmd_26, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_27), nt36672c_fhd_plus_90hz_video_on_cmd_27, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_28), nt36672c_fhd_plus_90hz_video_on_cmd_28, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_29), nt36672c_fhd_plus_90hz_video_on_cmd_29, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_30), nt36672c_fhd_plus_90hz_video_on_cmd_30, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_31), nt36672c_fhd_plus_90hz_video_on_cmd_31, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_32), nt36672c_fhd_plus_90hz_video_on_cmd_32, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_33), nt36672c_fhd_plus_90hz_video_on_cmd_33, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_34), nt36672c_fhd_plus_90hz_video_on_cmd_34, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_35), nt36672c_fhd_plus_90hz_video_on_cmd_35, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_36), nt36672c_fhd_plus_90hz_video_on_cmd_36, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_37), nt36672c_fhd_plus_90hz_video_on_cmd_37, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_38), nt36672c_fhd_plus_90hz_video_on_cmd_38, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_39), nt36672c_fhd_plus_90hz_video_on_cmd_39, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_40), nt36672c_fhd_plus_90hz_video_on_cmd_40, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_41), nt36672c_fhd_plus_90hz_video_on_cmd_41, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_42), nt36672c_fhd_plus_90hz_video_on_cmd_42, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_43), nt36672c_fhd_plus_90hz_video_on_cmd_43, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_44), nt36672c_fhd_plus_90hz_video_on_cmd_44, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_45), nt36672c_fhd_plus_90hz_video_on_cmd_45, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_46), nt36672c_fhd_plus_90hz_video_on_cmd_46, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_47), nt36672c_fhd_plus_90hz_video_on_cmd_47, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_48), nt36672c_fhd_plus_90hz_video_on_cmd_48, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_49), nt36672c_fhd_plus_90hz_video_on_cmd_49, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_50), nt36672c_fhd_plus_90hz_video_on_cmd_50, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_51), nt36672c_fhd_plus_90hz_video_on_cmd_51, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_52), nt36672c_fhd_plus_90hz_video_on_cmd_52, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_53), nt36672c_fhd_plus_90hz_video_on_cmd_53, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_54), nt36672c_fhd_plus_90hz_video_on_cmd_54, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_55), nt36672c_fhd_plus_90hz_video_on_cmd_55, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_56), nt36672c_fhd_plus_90hz_video_on_cmd_56, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_57), nt36672c_fhd_plus_90hz_video_on_cmd_57, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_58), nt36672c_fhd_plus_90hz_video_on_cmd_58, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_59), nt36672c_fhd_plus_90hz_video_on_cmd_59, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_60), nt36672c_fhd_plus_90hz_video_on_cmd_60, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_61), nt36672c_fhd_plus_90hz_video_on_cmd_61, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_62), nt36672c_fhd_plus_90hz_video_on_cmd_62, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_63), nt36672c_fhd_plus_90hz_video_on_cmd_63, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_64), nt36672c_fhd_plus_90hz_video_on_cmd_64, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_65), nt36672c_fhd_plus_90hz_video_on_cmd_65, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_66), nt36672c_fhd_plus_90hz_video_on_cmd_66, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_67), nt36672c_fhd_plus_90hz_video_on_cmd_67, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_68), nt36672c_fhd_plus_90hz_video_on_cmd_68, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_69), nt36672c_fhd_plus_90hz_video_on_cmd_69, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_70), nt36672c_fhd_plus_90hz_video_on_cmd_70, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_71), nt36672c_fhd_plus_90hz_video_on_cmd_71, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_72), nt36672c_fhd_plus_90hz_video_on_cmd_72, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_73), nt36672c_fhd_plus_90hz_video_on_cmd_73, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_74), nt36672c_fhd_plus_90hz_video_on_cmd_74, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_75), nt36672c_fhd_plus_90hz_video_on_cmd_75, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_76), nt36672c_fhd_plus_90hz_video_on_cmd_76, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_77), nt36672c_fhd_plus_90hz_video_on_cmd_77, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_78), nt36672c_fhd_plus_90hz_video_on_cmd_78, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_79), nt36672c_fhd_plus_90hz_video_on_cmd_79, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_80), nt36672c_fhd_plus_90hz_video_on_cmd_80, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_81), nt36672c_fhd_plus_90hz_video_on_cmd_81, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_82), nt36672c_fhd_plus_90hz_video_on_cmd_82, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_83), nt36672c_fhd_plus_90hz_video_on_cmd_83, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_84), nt36672c_fhd_plus_90hz_video_on_cmd_84, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_85), nt36672c_fhd_plus_90hz_video_on_cmd_85, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_86), nt36672c_fhd_plus_90hz_video_on_cmd_86, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_87), nt36672c_fhd_plus_90hz_video_on_cmd_87, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_88), nt36672c_fhd_plus_90hz_video_on_cmd_88, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_89), nt36672c_fhd_plus_90hz_video_on_cmd_89, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_90), nt36672c_fhd_plus_90hz_video_on_cmd_90, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_91), nt36672c_fhd_plus_90hz_video_on_cmd_91, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_92), nt36672c_fhd_plus_90hz_video_on_cmd_92, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_93), nt36672c_fhd_plus_90hz_video_on_cmd_93, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_94), nt36672c_fhd_plus_90hz_video_on_cmd_94, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_95), nt36672c_fhd_plus_90hz_video_on_cmd_95, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_96), nt36672c_fhd_plus_90hz_video_on_cmd_96, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_97), nt36672c_fhd_plus_90hz_video_on_cmd_97, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_98), nt36672c_fhd_plus_90hz_video_on_cmd_98, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_99), nt36672c_fhd_plus_90hz_video_on_cmd_99, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_100), nt36672c_fhd_plus_90hz_video_on_cmd_100, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_101), nt36672c_fhd_plus_90hz_video_on_cmd_101, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_102), nt36672c_fhd_plus_90hz_video_on_cmd_102, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_103), nt36672c_fhd_plus_90hz_video_on_cmd_103, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_104), nt36672c_fhd_plus_90hz_video_on_cmd_104, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_105), nt36672c_fhd_plus_90hz_video_on_cmd_105, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_106), nt36672c_fhd_plus_90hz_video_on_cmd_106, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_107), nt36672c_fhd_plus_90hz_video_on_cmd_107, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_108), nt36672c_fhd_plus_90hz_video_on_cmd_108, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_109), nt36672c_fhd_plus_90hz_video_on_cmd_109, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_110), nt36672c_fhd_plus_90hz_video_on_cmd_110, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_111), nt36672c_fhd_plus_90hz_video_on_cmd_111, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_112), nt36672c_fhd_plus_90hz_video_on_cmd_112, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_113), nt36672c_fhd_plus_90hz_video_on_cmd_113, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_114), nt36672c_fhd_plus_90hz_video_on_cmd_114, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_115), nt36672c_fhd_plus_90hz_video_on_cmd_115, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_116), nt36672c_fhd_plus_90hz_video_on_cmd_116, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_117), nt36672c_fhd_plus_90hz_video_on_cmd_117, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_118), nt36672c_fhd_plus_90hz_video_on_cmd_118, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_119), nt36672c_fhd_plus_90hz_video_on_cmd_119, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_120), nt36672c_fhd_plus_90hz_video_on_cmd_120, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_121), nt36672c_fhd_plus_90hz_video_on_cmd_121, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_122), nt36672c_fhd_plus_90hz_video_on_cmd_122, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_123), nt36672c_fhd_plus_90hz_video_on_cmd_123, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_124), nt36672c_fhd_plus_90hz_video_on_cmd_124, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_125), nt36672c_fhd_plus_90hz_video_on_cmd_125, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_126), nt36672c_fhd_plus_90hz_video_on_cmd_126, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_127), nt36672c_fhd_plus_90hz_video_on_cmd_127, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_128), nt36672c_fhd_plus_90hz_video_on_cmd_128, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_129), nt36672c_fhd_plus_90hz_video_on_cmd_129, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_130), nt36672c_fhd_plus_90hz_video_on_cmd_130, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_131), nt36672c_fhd_plus_90hz_video_on_cmd_131, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_132), nt36672c_fhd_plus_90hz_video_on_cmd_132, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_133), nt36672c_fhd_plus_90hz_video_on_cmd_133, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_134), nt36672c_fhd_plus_90hz_video_on_cmd_134, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_135), nt36672c_fhd_plus_90hz_video_on_cmd_135, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_136), nt36672c_fhd_plus_90hz_video_on_cmd_136, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_137), nt36672c_fhd_plus_90hz_video_on_cmd_137, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_138), nt36672c_fhd_plus_90hz_video_on_cmd_138, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_139), nt36672c_fhd_plus_90hz_video_on_cmd_139, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_140), nt36672c_fhd_plus_90hz_video_on_cmd_140, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_141), nt36672c_fhd_plus_90hz_video_on_cmd_141, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_142), nt36672c_fhd_plus_90hz_video_on_cmd_142, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_143), nt36672c_fhd_plus_90hz_video_on_cmd_143, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_144), nt36672c_fhd_plus_90hz_video_on_cmd_144, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_145), nt36672c_fhd_plus_90hz_video_on_cmd_145, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_146), nt36672c_fhd_plus_90hz_video_on_cmd_146, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_147), nt36672c_fhd_plus_90hz_video_on_cmd_147, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_148), nt36672c_fhd_plus_90hz_video_on_cmd_148, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_149), nt36672c_fhd_plus_90hz_video_on_cmd_149, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_150), nt36672c_fhd_plus_90hz_video_on_cmd_150, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_151), nt36672c_fhd_plus_90hz_video_on_cmd_151, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_152), nt36672c_fhd_plus_90hz_video_on_cmd_152, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_153), nt36672c_fhd_plus_90hz_video_on_cmd_153, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_154), nt36672c_fhd_plus_90hz_video_on_cmd_154, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_155), nt36672c_fhd_plus_90hz_video_on_cmd_155, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_156), nt36672c_fhd_plus_90hz_video_on_cmd_156, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_157), nt36672c_fhd_plus_90hz_video_on_cmd_157, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_158), nt36672c_fhd_plus_90hz_video_on_cmd_158, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_159), nt36672c_fhd_plus_90hz_video_on_cmd_159, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_160), nt36672c_fhd_plus_90hz_video_on_cmd_160, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_161), nt36672c_fhd_plus_90hz_video_on_cmd_161, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_162), nt36672c_fhd_plus_90hz_video_on_cmd_162, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_163), nt36672c_fhd_plus_90hz_video_on_cmd_163, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_164), nt36672c_fhd_plus_90hz_video_on_cmd_164, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_165), nt36672c_fhd_plus_90hz_video_on_cmd_165, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_166), nt36672c_fhd_plus_90hz_video_on_cmd_166, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_167), nt36672c_fhd_plus_90hz_video_on_cmd_167, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_168), nt36672c_fhd_plus_90hz_video_on_cmd_168, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_169), nt36672c_fhd_plus_90hz_video_on_cmd_169, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_170), nt36672c_fhd_plus_90hz_video_on_cmd_170, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_171), nt36672c_fhd_plus_90hz_video_on_cmd_171, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_172), nt36672c_fhd_plus_90hz_video_on_cmd_172, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_173), nt36672c_fhd_plus_90hz_video_on_cmd_173, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_174), nt36672c_fhd_plus_90hz_video_on_cmd_174, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_175), nt36672c_fhd_plus_90hz_video_on_cmd_175, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_176), nt36672c_fhd_plus_90hz_video_on_cmd_176, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_177), nt36672c_fhd_plus_90hz_video_on_cmd_177, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_178), nt36672c_fhd_plus_90hz_video_on_cmd_178, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_179), nt36672c_fhd_plus_90hz_video_on_cmd_179, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_180), nt36672c_fhd_plus_90hz_video_on_cmd_180, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_181), nt36672c_fhd_plus_90hz_video_on_cmd_181, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_182), nt36672c_fhd_plus_90hz_video_on_cmd_182, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_183), nt36672c_fhd_plus_90hz_video_on_cmd_183, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_184), nt36672c_fhd_plus_90hz_video_on_cmd_184, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_185), nt36672c_fhd_plus_90hz_video_on_cmd_185, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_186), nt36672c_fhd_plus_90hz_video_on_cmd_186, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_187), nt36672c_fhd_plus_90hz_video_on_cmd_187, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_188), nt36672c_fhd_plus_90hz_video_on_cmd_188, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_189), nt36672c_fhd_plus_90hz_video_on_cmd_189, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_190), nt36672c_fhd_plus_90hz_video_on_cmd_190, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_191), nt36672c_fhd_plus_90hz_video_on_cmd_191, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_192), nt36672c_fhd_plus_90hz_video_on_cmd_192, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_193), nt36672c_fhd_plus_90hz_video_on_cmd_193, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_194), nt36672c_fhd_plus_90hz_video_on_cmd_194, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_195), nt36672c_fhd_plus_90hz_video_on_cmd_195, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_196), nt36672c_fhd_plus_90hz_video_on_cmd_196, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_197), nt36672c_fhd_plus_90hz_video_on_cmd_197, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_198), nt36672c_fhd_plus_90hz_video_on_cmd_198, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_199), nt36672c_fhd_plus_90hz_video_on_cmd_199, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_200), nt36672c_fhd_plus_90hz_video_on_cmd_200, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_201), nt36672c_fhd_plus_90hz_video_on_cmd_201, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_202), nt36672c_fhd_plus_90hz_video_on_cmd_202, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_203), nt36672c_fhd_plus_90hz_video_on_cmd_203, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_204), nt36672c_fhd_plus_90hz_video_on_cmd_204, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_205), nt36672c_fhd_plus_90hz_video_on_cmd_205, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_206), nt36672c_fhd_plus_90hz_video_on_cmd_206, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_207), nt36672c_fhd_plus_90hz_video_on_cmd_207, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_208), nt36672c_fhd_plus_90hz_video_on_cmd_208, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_209), nt36672c_fhd_plus_90hz_video_on_cmd_209, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_210), nt36672c_fhd_plus_90hz_video_on_cmd_210, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_211), nt36672c_fhd_plus_90hz_video_on_cmd_211, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_212), nt36672c_fhd_plus_90hz_video_on_cmd_212, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_213), nt36672c_fhd_plus_90hz_video_on_cmd_213, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_214), nt36672c_fhd_plus_90hz_video_on_cmd_214, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_215), nt36672c_fhd_plus_90hz_video_on_cmd_215, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_216), nt36672c_fhd_plus_90hz_video_on_cmd_216, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_217), nt36672c_fhd_plus_90hz_video_on_cmd_217, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_218), nt36672c_fhd_plus_90hz_video_on_cmd_218, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_219), nt36672c_fhd_plus_90hz_video_on_cmd_219, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_220), nt36672c_fhd_plus_90hz_video_on_cmd_220, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_221), nt36672c_fhd_plus_90hz_video_on_cmd_221, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_222), nt36672c_fhd_plus_90hz_video_on_cmd_222, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_223), nt36672c_fhd_plus_90hz_video_on_cmd_223, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_224), nt36672c_fhd_plus_90hz_video_on_cmd_224, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_225), nt36672c_fhd_plus_90hz_video_on_cmd_225, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_226), nt36672c_fhd_plus_90hz_video_on_cmd_226, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_227), nt36672c_fhd_plus_90hz_video_on_cmd_227, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_228), nt36672c_fhd_plus_90hz_video_on_cmd_228, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_229), nt36672c_fhd_plus_90hz_video_on_cmd_229, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_230), nt36672c_fhd_plus_90hz_video_on_cmd_230, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_231), nt36672c_fhd_plus_90hz_video_on_cmd_231, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_232), nt36672c_fhd_plus_90hz_video_on_cmd_232, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_233), nt36672c_fhd_plus_90hz_video_on_cmd_233, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_234), nt36672c_fhd_plus_90hz_video_on_cmd_234, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_235), nt36672c_fhd_plus_90hz_video_on_cmd_235, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_236), nt36672c_fhd_plus_90hz_video_on_cmd_236, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_237), nt36672c_fhd_plus_90hz_video_on_cmd_237, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_238), nt36672c_fhd_plus_90hz_video_on_cmd_238, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_239), nt36672c_fhd_plus_90hz_video_on_cmd_239, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_240), nt36672c_fhd_plus_90hz_video_on_cmd_240, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_241), nt36672c_fhd_plus_90hz_video_on_cmd_241, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_242), nt36672c_fhd_plus_90hz_video_on_cmd_242, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_243), nt36672c_fhd_plus_90hz_video_on_cmd_243, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_244), nt36672c_fhd_plus_90hz_video_on_cmd_244, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_245), nt36672c_fhd_plus_90hz_video_on_cmd_245, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_246), nt36672c_fhd_plus_90hz_video_on_cmd_246, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_247), nt36672c_fhd_plus_90hz_video_on_cmd_247, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_248), nt36672c_fhd_plus_90hz_video_on_cmd_248, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_249), nt36672c_fhd_plus_90hz_video_on_cmd_249, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_250), nt36672c_fhd_plus_90hz_video_on_cmd_250, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_251), nt36672c_fhd_plus_90hz_video_on_cmd_251, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_252), nt36672c_fhd_plus_90hz_video_on_cmd_252, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_253), nt36672c_fhd_plus_90hz_video_on_cmd_253, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_254), nt36672c_fhd_plus_90hz_video_on_cmd_254, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_255), nt36672c_fhd_plus_90hz_video_on_cmd_255, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_256), nt36672c_fhd_plus_90hz_video_on_cmd_256, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_257), nt36672c_fhd_plus_90hz_video_on_cmd_257, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_258), nt36672c_fhd_plus_90hz_video_on_cmd_258, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_259), nt36672c_fhd_plus_90hz_video_on_cmd_259, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_260), nt36672c_fhd_plus_90hz_video_on_cmd_260, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_261), nt36672c_fhd_plus_90hz_video_on_cmd_261, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_262), nt36672c_fhd_plus_90hz_video_on_cmd_262, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_263), nt36672c_fhd_plus_90hz_video_on_cmd_263, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_264), nt36672c_fhd_plus_90hz_video_on_cmd_264, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_265), nt36672c_fhd_plus_90hz_video_on_cmd_265, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_266), nt36672c_fhd_plus_90hz_video_on_cmd_266, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_267), nt36672c_fhd_plus_90hz_video_on_cmd_267, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_268), nt36672c_fhd_plus_90hz_video_on_cmd_268, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_269), nt36672c_fhd_plus_90hz_video_on_cmd_269, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_270), nt36672c_fhd_plus_90hz_video_on_cmd_270, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_271), nt36672c_fhd_plus_90hz_video_on_cmd_271, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_272), nt36672c_fhd_plus_90hz_video_on_cmd_272, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_273), nt36672c_fhd_plus_90hz_video_on_cmd_273, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_274), nt36672c_fhd_plus_90hz_video_on_cmd_274, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_275), nt36672c_fhd_plus_90hz_video_on_cmd_275, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_276), nt36672c_fhd_plus_90hz_video_on_cmd_276, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_277), nt36672c_fhd_plus_90hz_video_on_cmd_277, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_278), nt36672c_fhd_plus_90hz_video_on_cmd_278, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_279), nt36672c_fhd_plus_90hz_video_on_cmd_279, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_280), nt36672c_fhd_plus_90hz_video_on_cmd_280, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_281), nt36672c_fhd_plus_90hz_video_on_cmd_281, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_282), nt36672c_fhd_plus_90hz_video_on_cmd_282, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_283), nt36672c_fhd_plus_90hz_video_on_cmd_283, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_284), nt36672c_fhd_plus_90hz_video_on_cmd_284, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_285), nt36672c_fhd_plus_90hz_video_on_cmd_285, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_286), nt36672c_fhd_plus_90hz_video_on_cmd_286, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_287), nt36672c_fhd_plus_90hz_video_on_cmd_287, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_288), nt36672c_fhd_plus_90hz_video_on_cmd_288, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_289), nt36672c_fhd_plus_90hz_video_on_cmd_289, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_290), nt36672c_fhd_plus_90hz_video_on_cmd_290, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_291), nt36672c_fhd_plus_90hz_video_on_cmd_291, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_292), nt36672c_fhd_plus_90hz_video_on_cmd_292, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_293), nt36672c_fhd_plus_90hz_video_on_cmd_293, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_294), nt36672c_fhd_plus_90hz_video_on_cmd_294, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_295), nt36672c_fhd_plus_90hz_video_on_cmd_295, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_296), nt36672c_fhd_plus_90hz_video_on_cmd_296, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_297), nt36672c_fhd_plus_90hz_video_on_cmd_297, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_298), nt36672c_fhd_plus_90hz_video_on_cmd_298, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_299), nt36672c_fhd_plus_90hz_video_on_cmd_299, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_300), nt36672c_fhd_plus_90hz_video_on_cmd_300, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_301), nt36672c_fhd_plus_90hz_video_on_cmd_301, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_302), nt36672c_fhd_plus_90hz_video_on_cmd_302, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_303), nt36672c_fhd_plus_90hz_video_on_cmd_303, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_304), nt36672c_fhd_plus_90hz_video_on_cmd_304, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_305), nt36672c_fhd_plus_90hz_video_on_cmd_305, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_306), nt36672c_fhd_plus_90hz_video_on_cmd_306, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_307), nt36672c_fhd_plus_90hz_video_on_cmd_307, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_308), nt36672c_fhd_plus_90hz_video_on_cmd_308, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_309), nt36672c_fhd_plus_90hz_video_on_cmd_309, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_310), nt36672c_fhd_plus_90hz_video_on_cmd_310, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_311), nt36672c_fhd_plus_90hz_video_on_cmd_311, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_312), nt36672c_fhd_plus_90hz_video_on_cmd_312, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_313), nt36672c_fhd_plus_90hz_video_on_cmd_313, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_314), nt36672c_fhd_plus_90hz_video_on_cmd_314, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_315), nt36672c_fhd_plus_90hz_video_on_cmd_315, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_316), nt36672c_fhd_plus_90hz_video_on_cmd_316, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_317), nt36672c_fhd_plus_90hz_video_on_cmd_317, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_318), nt36672c_fhd_plus_90hz_video_on_cmd_318, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_319), nt36672c_fhd_plus_90hz_video_on_cmd_319, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_320), nt36672c_fhd_plus_90hz_video_on_cmd_320, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_321), nt36672c_fhd_plus_90hz_video_on_cmd_321, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_322), nt36672c_fhd_plus_90hz_video_on_cmd_322, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_323), nt36672c_fhd_plus_90hz_video_on_cmd_323, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_324), nt36672c_fhd_plus_90hz_video_on_cmd_324, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_325), nt36672c_fhd_plus_90hz_video_on_cmd_325, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_326), nt36672c_fhd_plus_90hz_video_on_cmd_326, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_327), nt36672c_fhd_plus_90hz_video_on_cmd_327, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_328), nt36672c_fhd_plus_90hz_video_on_cmd_328, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_329), nt36672c_fhd_plus_90hz_video_on_cmd_329, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_330), nt36672c_fhd_plus_90hz_video_on_cmd_330, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_331), nt36672c_fhd_plus_90hz_video_on_cmd_331, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_332), nt36672c_fhd_plus_90hz_video_on_cmd_332, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_333), nt36672c_fhd_plus_90hz_video_on_cmd_333, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_334), nt36672c_fhd_plus_90hz_video_on_cmd_334, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_335), nt36672c_fhd_plus_90hz_video_on_cmd_335, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_336), nt36672c_fhd_plus_90hz_video_on_cmd_336, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_337), nt36672c_fhd_plus_90hz_video_on_cmd_337, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_338), nt36672c_fhd_plus_90hz_video_on_cmd_338, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_339), nt36672c_fhd_plus_90hz_video_on_cmd_339, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_340), nt36672c_fhd_plus_90hz_video_on_cmd_340, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_341), nt36672c_fhd_plus_90hz_video_on_cmd_341, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_342), nt36672c_fhd_plus_90hz_video_on_cmd_342, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_343), nt36672c_fhd_plus_90hz_video_on_cmd_343, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_344), nt36672c_fhd_plus_90hz_video_on_cmd_344, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_345), nt36672c_fhd_plus_90hz_video_on_cmd_345, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_346), nt36672c_fhd_plus_90hz_video_on_cmd_346, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_347), nt36672c_fhd_plus_90hz_video_on_cmd_347, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_348), nt36672c_fhd_plus_90hz_video_on_cmd_348, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_349), nt36672c_fhd_plus_90hz_video_on_cmd_349, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_350), nt36672c_fhd_plus_90hz_video_on_cmd_350, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_351), nt36672c_fhd_plus_90hz_video_on_cmd_351, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_352), nt36672c_fhd_plus_90hz_video_on_cmd_352, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_353), nt36672c_fhd_plus_90hz_video_on_cmd_353, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_354), nt36672c_fhd_plus_90hz_video_on_cmd_354, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_355), nt36672c_fhd_plus_90hz_video_on_cmd_355, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_356), nt36672c_fhd_plus_90hz_video_on_cmd_356, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_357), nt36672c_fhd_plus_90hz_video_on_cmd_357, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_358), nt36672c_fhd_plus_90hz_video_on_cmd_358, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_359), nt36672c_fhd_plus_90hz_video_on_cmd_359, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_360), nt36672c_fhd_plus_90hz_video_on_cmd_360, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_361), nt36672c_fhd_plus_90hz_video_on_cmd_361, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_362), nt36672c_fhd_plus_90hz_video_on_cmd_362, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_363), nt36672c_fhd_plus_90hz_video_on_cmd_363, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_364), nt36672c_fhd_plus_90hz_video_on_cmd_364, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_365), nt36672c_fhd_plus_90hz_video_on_cmd_365, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_366), nt36672c_fhd_plus_90hz_video_on_cmd_366, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_367), nt36672c_fhd_plus_90hz_video_on_cmd_367, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_368), nt36672c_fhd_plus_90hz_video_on_cmd_368, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_369), nt36672c_fhd_plus_90hz_video_on_cmd_369, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_370), nt36672c_fhd_plus_90hz_video_on_cmd_370, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_371), nt36672c_fhd_plus_90hz_video_on_cmd_371, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_372), nt36672c_fhd_plus_90hz_video_on_cmd_372, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_373), nt36672c_fhd_plus_90hz_video_on_cmd_373, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_374), nt36672c_fhd_plus_90hz_video_on_cmd_374, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_375), nt36672c_fhd_plus_90hz_video_on_cmd_375, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_376), nt36672c_fhd_plus_90hz_video_on_cmd_376, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_377), nt36672c_fhd_plus_90hz_video_on_cmd_377, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_378), nt36672c_fhd_plus_90hz_video_on_cmd_378, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_379), nt36672c_fhd_plus_90hz_video_on_cmd_379, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_380), nt36672c_fhd_plus_90hz_video_on_cmd_380, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_381), nt36672c_fhd_plus_90hz_video_on_cmd_381, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_382), nt36672c_fhd_plus_90hz_video_on_cmd_382, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_383), nt36672c_fhd_plus_90hz_video_on_cmd_383, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_384), nt36672c_fhd_plus_90hz_video_on_cmd_384, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_385), nt36672c_fhd_plus_90hz_video_on_cmd_385, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_386), nt36672c_fhd_plus_90hz_video_on_cmd_386, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_387), nt36672c_fhd_plus_90hz_video_on_cmd_387, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_388), nt36672c_fhd_plus_90hz_video_on_cmd_388, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_389), nt36672c_fhd_plus_90hz_video_on_cmd_389, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_390), nt36672c_fhd_plus_90hz_video_on_cmd_390, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_391), nt36672c_fhd_plus_90hz_video_on_cmd_391, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_392), nt36672c_fhd_plus_90hz_video_on_cmd_392, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_393), nt36672c_fhd_plus_90hz_video_on_cmd_393, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_394), nt36672c_fhd_plus_90hz_video_on_cmd_394, 0 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_395), nt36672c_fhd_plus_90hz_video_on_cmd_395, 200 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_on_cmd_396), nt36672c_fhd_plus_90hz_video_on_cmd_396, 150 },
};

static char nt36672c_fhd_plus_90hz_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char nt36672c_fhd_plus_90hz_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd nt36672c_fhd_plus_90hz_video_off_command[] = {
	{ sizeof(nt36672c_fhd_plus_90hz_video_off_cmd_0), nt36672c_fhd_plus_90hz_video_off_cmd_0, 16 },
	{ sizeof(nt36672c_fhd_plus_90hz_video_off_cmd_1), nt36672c_fhd_plus_90hz_video_off_cmd_1, 50 },
};

static struct command_state nt36672c_fhd_plus_90hz_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 0,
};

static struct commandpanel_info nt36672c_fhd_plus_90hz_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info nt36672c_fhd_plus_90hz_video_video_panel = {
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

static struct lane_configuration nt36672c_fhd_plus_90hz_video_lane_config = {
	.dsi_lanes = 3,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 0,
	.force_clk_lane_hs = 0,
};

static const uint32_t nt36672c_fhd_plus_90hz_video_timings[] = {
	
};

static struct panel_timing nt36672c_fhd_plus_90hz_video_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence nt36672c_fhd_plus_90hz_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static inline void panel_nt36672c_fhd_plus_90hz_video_select(struct panel_struct *panel,
							     struct msm_panel_info *pinfo,
							     struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &nt36672c_fhd_plus_90hz_video_panel_data;
	panel->panelres = &nt36672c_fhd_plus_90hz_video_panel_res;
	panel->color = &nt36672c_fhd_plus_90hz_video_color;
	panel->videopanel = &nt36672c_fhd_plus_90hz_video_video_panel;
	panel->commandpanel = &nt36672c_fhd_plus_90hz_video_command_panel;
	panel->state = &nt36672c_fhd_plus_90hz_video_state;
	panel->laneconfig = &nt36672c_fhd_plus_90hz_video_lane_config;
	panel->paneltiminginfo = &nt36672c_fhd_plus_90hz_video_timing_info;
	panel->panelresetseq = &nt36672c_fhd_plus_90hz_video_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = nt36672c_fhd_plus_90hz_video_on_command;
	pinfo->mipi.panel_off_cmds = nt36672c_fhd_plus_90hz_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(nt36672c_fhd_plus_90hz_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(nt36672c_fhd_plus_90hz_video_off_command);
	memcpy(phy_db->timing, nt36672c_fhd_plus_90hz_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_NT36672C_FHD_PLUS_90HZ_VIDEO_H_ */
