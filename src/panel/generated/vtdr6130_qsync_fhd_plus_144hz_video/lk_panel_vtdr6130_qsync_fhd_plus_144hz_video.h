// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_VTDR6130_QSYNC_FHD_PLUS_144HZ_VIDEO_H_
#define _PANEL_VTDR6130_QSYNC_FHD_PLUS_144HZ_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config vtdr6130_qsync_fhd_plus_144hz_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_vtdr6130_qsync_fhd_plus_144hz_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 144,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution vtdr6130_qsync_fhd_plus_144hz_video_panel_res = {
	.panel_width = 1080,
	.panel_height = 2400,
	.hfront_porch = 20,
	.hback_porch = 20,
	.hpulse_width = 2,
	.hsync_skew = 0,
	.vfront_porch = 20,
	.vback_porch = 18,
	.vpulse_width = 2,
	/* Borders not supported yet */
};

static struct color_info vtdr6130_qsync_fhd_plus_144hz_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_0[] = {
	0x02, 0x00, 0x39, 0xc0, 0x03, 0x01, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_1[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_2[] = {
	0x02, 0x00, 0x39, 0xc0, 0x53, 0x20, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_3[] = {
	0x03, 0x00, 0x39, 0xc0, 0x51, 0x00, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_4[] = {
	0x02, 0x00, 0x39, 0xc0, 0x59, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_5[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6c, 0x01, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_6[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6d, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_7[] = {
	0x02, 0x00, 0x39, 0xc0, 0x6f, 0x01, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_8[] = {
	0x5f, 0x00, 0x39, 0xc0, 0x70, 0x12, 0x00, 0x00,
	0xab, 0x30, 0x80, 0x09, 0x60, 0x04, 0x38, 0x00,
	0x28, 0x02, 0x1c, 0x02, 0x1c, 0x02, 0x00, 0x02,
	0x0e, 0x00, 0x20, 0x03, 0xdd, 0x00, 0x07, 0x00,
	0x0c, 0x02, 0x77, 0x02, 0x8b, 0x18, 0x00, 0x10,
	0xf0, 0x07, 0x10, 0x20, 0x00, 0x06, 0x0f, 0x0f,
	0x33, 0x0e, 0x1c, 0x2a, 0x38, 0x46, 0x54, 0x62,
	0x69, 0x70, 0x77, 0x79, 0x7b, 0x7d, 0x7e, 0x02,
	0x02, 0x22, 0x00, 0x2a, 0x40, 0x2a, 0xbe, 0x3a,
	0xfc, 0x3a, 0xfa, 0x3a, 0xf8, 0x3b, 0x38, 0x3b,
	0x78, 0x3b, 0xb6, 0x4b, 0xb6, 0x4b, 0xf4, 0x4b,
	0xf4, 0x6c, 0x34, 0x84, 0x74, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_9[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x10, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_10[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x16, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_11[] = {
	0x03, 0x00, 0x39, 0xc0, 0xeb, 0x00, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_12[] = {
	0x16, 0x00, 0x39, 0xc0, 0xb1, 0x01, 0x38, 0x00,
	0x14, 0x00, 0x1c, 0x00, 0x01, 0x66, 0x00, 0x14,
	0x00, 0x14, 0x00, 0x01, 0x66, 0x00, 0x14, 0x05,
	0xcc, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_13[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x13, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_14[] = {
	0x18, 0x00, 0x39, 0xc0, 0xce, 0x09, 0x11, 0x09,
	0x11, 0x08, 0xc1, 0x07, 0xfa, 0x05, 0xa4, 0x00,
	0x3c, 0x00, 0x34, 0x00, 0x24, 0x00, 0x0c, 0x00,
	0x0c, 0x04, 0x00, 0x35
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_15[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x14, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_16[] = {
	0x03, 0x00, 0x39, 0xc0, 0xb2, 0x03, 0x33, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_17[] = {
	0x0d, 0x00, 0x39, 0xc0, 0xb4, 0x00, 0x33, 0x00,
	0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x3e, 0x00,
	0x00, 0xff, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_18[] = {
	0x0a, 0x00, 0x39, 0xc0, 0xb5, 0x00, 0x09, 0x09,
	0x09, 0x09, 0x09, 0x09, 0x06, 0x01, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_19[] = {
	0x07, 0x00, 0x39, 0xc0, 0xb9, 0x00, 0x00, 0x08,
	0x09, 0x09, 0x09, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_20[] = {
	0x0d, 0x00, 0x39, 0xc0, 0xbc, 0x10, 0x00, 0x00,
	0x06, 0x11, 0x09, 0x3b, 0x09, 0x47, 0x09, 0x47,
	0x00, 0xff, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_21[] = {
	0x0d, 0x00, 0x39, 0xc0, 0xbe, 0x10, 0x10, 0x00,
	0x08, 0x22, 0x09, 0x19, 0x09, 0x25, 0x09, 0x25,
	0x00, 0xff, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_22[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x80, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_23[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x14, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_24[] = {
	0x04, 0x00, 0x39, 0xc0, 0xfa, 0x08, 0x08, 0x08
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_25[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x81, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_26[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x05, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_27[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf3, 0x0f, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_28[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_29[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x82, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_30[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf9, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_31[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x51, 0x83, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_32[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x04, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_33[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf8, 0x00, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_34[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_35[] = {
	0x02, 0x00, 0x39, 0xc0, 0x65, 0x01, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_36[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf4, 0x9a, 0xff, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_37[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x00, 0xff
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_38[] = {
	0x11, 0x00, 0x05, 0x80
};
static char vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_39[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd vtdr6130_qsync_fhd_plus_144hz_video_on_command[] = {
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_0), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_0, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_1), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_1, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_2), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_2, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_3), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_3, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_4), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_4, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_5), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_5, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_6), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_6, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_7), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_7, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_8), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_8, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_9), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_9, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_10), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_10, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_11), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_11, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_12), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_12, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_13), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_13, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_14), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_14, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_15), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_15, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_16), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_16, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_17), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_17, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_18), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_18, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_19), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_19, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_20), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_20, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_21), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_21, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_22), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_22, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_23), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_23, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_24), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_24, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_25), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_25, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_26), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_26, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_27), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_27, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_28), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_28, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_29), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_29, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_30), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_30, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_31), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_31, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_32), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_32, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_33), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_33, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_34), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_34, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_35), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_35, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_36), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_36, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_37), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_37, 0 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_38), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_38, 120 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_39), vtdr6130_qsync_fhd_plus_144hz_video_on_cmd_39, 20 },
};

static char vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd vtdr6130_qsync_fhd_plus_144hz_video_off_command[] = {
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_0), vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_0, 20 },
	{ sizeof(vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_1), vtdr6130_qsync_fhd_plus_144hz_video_off_cmd_1, 120 },
};

static struct command_state vtdr6130_qsync_fhd_plus_144hz_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info vtdr6130_qsync_fhd_plus_144hz_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info vtdr6130_qsync_fhd_plus_144hz_video_video_panel = {
	.hsync_pulse = 0,
	.hfp_power_mode = 0,
	.hbp_power_mode = 0,
	.hsa_power_mode = 0,
	.bllp_eof_power_mode = 1,
	.bllp_power_mode = 1,
	.traffic_mode = 1,
	/* This is bllp_eof_power_mode and bllp_power_mode combined */
	.bllp_eof_power = 1 << 3 | 1 << 0,
};

static struct lane_configuration vtdr6130_qsync_fhd_plus_144hz_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t vtdr6130_qsync_fhd_plus_144hz_video_timings[] = {
	
};

static struct panel_timing vtdr6130_qsync_fhd_plus_144hz_video_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence vtdr6130_qsync_fhd_plus_144hz_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static inline void panel_vtdr6130_qsync_fhd_plus_144hz_video_select(struct panel_struct *panel,
								    struct msm_panel_info *pinfo,
								    struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &vtdr6130_qsync_fhd_plus_144hz_video_panel_data;
	panel->panelres = &vtdr6130_qsync_fhd_plus_144hz_video_panel_res;
	panel->color = &vtdr6130_qsync_fhd_plus_144hz_video_color;
	panel->videopanel = &vtdr6130_qsync_fhd_plus_144hz_video_video_panel;
	panel->commandpanel = &vtdr6130_qsync_fhd_plus_144hz_video_command_panel;
	panel->state = &vtdr6130_qsync_fhd_plus_144hz_video_state;
	panel->laneconfig = &vtdr6130_qsync_fhd_plus_144hz_video_lane_config;
	panel->paneltiminginfo = &vtdr6130_qsync_fhd_plus_144hz_video_timing_info;
	panel->panelresetseq = &vtdr6130_qsync_fhd_plus_144hz_video_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = vtdr6130_qsync_fhd_plus_144hz_video_on_command;
	pinfo->mipi.panel_off_cmds = vtdr6130_qsync_fhd_plus_144hz_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(vtdr6130_qsync_fhd_plus_144hz_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(vtdr6130_qsync_fhd_plus_144hz_video_off_command);
	memcpy(phy_db->timing, vtdr6130_qsync_fhd_plus_144hz_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_VTDR6130_QSYNC_FHD_PLUS_144HZ_VIDEO_H_ */
