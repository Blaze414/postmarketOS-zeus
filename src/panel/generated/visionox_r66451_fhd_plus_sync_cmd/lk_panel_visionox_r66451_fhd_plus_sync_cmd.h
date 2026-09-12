// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_VISIONOX_R66451_FHD_PLUS_SYNC_CMD_H_
#define _PANEL_VISIONOX_R66451_FHD_PLUS_SYNC_CMD_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config visionox_r66451_fhd_plus_sync_cmd_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_visionox_r66451_fhd_plus_sync_cmd",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 1,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution visionox_r66451_fhd_plus_sync_cmd_panel_res = {
	.panel_width = 1080,
	.panel_height = 2340,
	.hfront_porch = 95,
	.hback_porch = 40,
	.hpulse_width = 1,
	.hsync_skew = 0,
	.vfront_porch = 25,
	.vback_porch = 4,
	.vpulse_width = 1,
	/* Borders not supported yet */
};

static struct color_info visionox_r66451_fhd_plus_sync_cmd_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_0[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_1[] = {
	0x0c, 0x00, 0x39, 0xc0, 0xc2, 0x09, 0x24, 0x0c,
	0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x09, 0x3c
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_2[] = {
	0x1a, 0x00, 0x39, 0xc0, 0xd7, 0x00, 0xb9, 0x3c,
	0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a, 0x00, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x3c,
	0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_3[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x80, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_4[] = {
	0x14, 0x00, 0x39, 0xc0, 0xde, 0x40, 0x00, 0x18,
	0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x10, 0x00,
	0x18, 0x00, 0x18, 0x00, 0x18, 0x02, 0x00, 0x00
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_5[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x04, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_6[] = {
	0x03, 0x00, 0x39, 0xc0, 0xe8, 0x00, 0x02, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_7[] = {
	0x03, 0x00, 0x39, 0xc0, 0xe4, 0x00, 0x08, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_8[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_9[] = {
	0x11, 0x00, 0x39, 0xc0, 0xc4, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x02, 0x00, 0x00, 0x00, 0x32, 0xff, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_10[] = {
	0x19, 0x00, 0x39, 0xc0, 0xcf, 0x64, 0x0b, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0b,
	0x77, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x03, 0xff, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_11[] = {
	0x15, 0x00, 0x39, 0xc0, 0xd3, 0x45, 0x00, 0x00,
	0x01, 0x13, 0x15, 0x00, 0x15, 0x07, 0x0f, 0x77,
	0x77, 0x77, 0x37, 0xb2, 0x11, 0x00, 0xa0, 0x3c,
	0x9c, 0xff, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_12[] = {
	0x1a, 0x00, 0x39, 0xc0, 0xd7, 0x00, 0xb9, 0x34,
	0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a, 0x00, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x34,
	0x00, 0x40, 0x04, 0x00, 0xa0, 0x0a, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_13[] = {
	0x34, 0x00, 0x39, 0xc0, 0xd8, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x00,
	0x3a, 0x00, 0x3a, 0x00, 0x3a, 0x00, 0x3a, 0x05,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0a, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0a, 0x00, 0x32, 0x00, 0x0a, 0x00, 0x22
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_14[] = {
	0x2b, 0x00, 0x39, 0xc0, 0xdf, 0x50, 0x42, 0x58,
	0x81, 0x2d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x6b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x0f, 0xff, 0xd4, 0x0e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x53, 0xf1, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_15[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf7, 0x01, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_16[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x80, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_17[] = {
	0x0a, 0x00, 0x39, 0xc0, 0xe4, 0x34, 0xb4, 0x00,
	0x00, 0x00, 0x39, 0x04, 0x09, 0x34, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_18[] = {
	0x02, 0x00, 0x39, 0xc0, 0xe6, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_19[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x04, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_20[] = {
	0x03, 0x00, 0x39, 0xc0, 0xdf, 0x50, 0x40, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_21[] = {
	0x06, 0x00, 0x39, 0xc0, 0xf3, 0x50, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_22[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf2, 0x11, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_23[] = {
	0x06, 0x00, 0x39, 0xc0, 0xf3, 0x01, 0x00, 0x00,
	0x00, 0x01, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_24[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf4, 0x00, 0x02, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_25[] = {
	0x02, 0x00, 0x39, 0xc0, 0xf2, 0x19, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_26[] = {
	0x03, 0x00, 0x39, 0xc0, 0xdf, 0x50, 0x42, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_27[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_28[] = {
	0x05, 0x00, 0x39, 0xc0, 0x2a, 0x00, 0x00, 0x04,
	0x37, 0xff, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_29[] = {
	0x05, 0x00, 0x39, 0xc0, 0x2b, 0x00, 0x00, 0x09,
	0x23, 0xff, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_30[] = {
	0x11, 0x00, 0x05, 0x80
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_31[] = {
	0x29, 0x00, 0x05, 0x80
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_32[] = {
	0x02, 0x00, 0x39, 0xc0, 0xb0, 0x00, 0xff, 0xff
};
static char visionox_r66451_fhd_plus_sync_cmd_on_cmd_33[] = {
	0x1a, 0x00, 0x39, 0xc0, 0xc2, 0x09, 0x24, 0x0c,
	0x00, 0x00, 0x0c, 0x09, 0x3c, 0x00, 0x09, 0x3c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x30, 0x00, 0x6c, 0xff, 0xff
};

static struct mipi_dsi_cmd visionox_r66451_fhd_plus_sync_cmd_on_command[] = {
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_0), visionox_r66451_fhd_plus_sync_cmd_on_cmd_0, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_1), visionox_r66451_fhd_plus_sync_cmd_on_cmd_1, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_2), visionox_r66451_fhd_plus_sync_cmd_on_cmd_2, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_3), visionox_r66451_fhd_plus_sync_cmd_on_cmd_3, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_4), visionox_r66451_fhd_plus_sync_cmd_on_cmd_4, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_5), visionox_r66451_fhd_plus_sync_cmd_on_cmd_5, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_6), visionox_r66451_fhd_plus_sync_cmd_on_cmd_6, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_7), visionox_r66451_fhd_plus_sync_cmd_on_cmd_7, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_8), visionox_r66451_fhd_plus_sync_cmd_on_cmd_8, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_9), visionox_r66451_fhd_plus_sync_cmd_on_cmd_9, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_10), visionox_r66451_fhd_plus_sync_cmd_on_cmd_10, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_11), visionox_r66451_fhd_plus_sync_cmd_on_cmd_11, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_12), visionox_r66451_fhd_plus_sync_cmd_on_cmd_12, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_13), visionox_r66451_fhd_plus_sync_cmd_on_cmd_13, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_14), visionox_r66451_fhd_plus_sync_cmd_on_cmd_14, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_15), visionox_r66451_fhd_plus_sync_cmd_on_cmd_15, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_16), visionox_r66451_fhd_plus_sync_cmd_on_cmd_16, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_17), visionox_r66451_fhd_plus_sync_cmd_on_cmd_17, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_18), visionox_r66451_fhd_plus_sync_cmd_on_cmd_18, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_19), visionox_r66451_fhd_plus_sync_cmd_on_cmd_19, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_20), visionox_r66451_fhd_plus_sync_cmd_on_cmd_20, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_21), visionox_r66451_fhd_plus_sync_cmd_on_cmd_21, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_22), visionox_r66451_fhd_plus_sync_cmd_on_cmd_22, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_23), visionox_r66451_fhd_plus_sync_cmd_on_cmd_23, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_24), visionox_r66451_fhd_plus_sync_cmd_on_cmd_24, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_25), visionox_r66451_fhd_plus_sync_cmd_on_cmd_25, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_26), visionox_r66451_fhd_plus_sync_cmd_on_cmd_26, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_27), visionox_r66451_fhd_plus_sync_cmd_on_cmd_27, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_28), visionox_r66451_fhd_plus_sync_cmd_on_cmd_28, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_29), visionox_r66451_fhd_plus_sync_cmd_on_cmd_29, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_30), visionox_r66451_fhd_plus_sync_cmd_on_cmd_30, 120 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_31), visionox_r66451_fhd_plus_sync_cmd_on_cmd_31, 20 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_32), visionox_r66451_fhd_plus_sync_cmd_on_cmd_32, 0 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_on_cmd_33), visionox_r66451_fhd_plus_sync_cmd_on_cmd_33, 0 },
};

static char visionox_r66451_fhd_plus_sync_cmd_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char visionox_r66451_fhd_plus_sync_cmd_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd visionox_r66451_fhd_plus_sync_cmd_off_command[] = {
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_off_cmd_0), visionox_r66451_fhd_plus_sync_cmd_off_cmd_0, 20 },
	{ sizeof(visionox_r66451_fhd_plus_sync_cmd_off_cmd_1), visionox_r66451_fhd_plus_sync_cmd_off_cmd_1, 120 },
};

static struct command_state visionox_r66451_fhd_plus_sync_cmd_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info visionox_r66451_fhd_plus_sync_cmd_command_panel = {
	/* FIXME: This is a command mode panel */
};

static struct videopanel_info visionox_r66451_fhd_plus_sync_cmd_video_panel = {
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

static struct lane_configuration visionox_r66451_fhd_plus_sync_cmd_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t visionox_r66451_fhd_plus_sync_cmd_timings[] = {
	
};

static struct panel_timing visionox_r66451_fhd_plus_sync_cmd_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence visionox_r66451_fhd_plus_sync_cmd_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static struct backlight visionox_r66451_fhd_plus_sync_cmd_backlight = {
	.bl_interface_type = BL_DCS,
	.bl_min_level = 1,
	.bl_max_level = 4095,
};

static inline void panel_visionox_r66451_fhd_plus_sync_cmd_select(struct panel_struct *panel,
								  struct msm_panel_info *pinfo,
								  struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &visionox_r66451_fhd_plus_sync_cmd_panel_data;
	panel->panelres = &visionox_r66451_fhd_plus_sync_cmd_panel_res;
	panel->color = &visionox_r66451_fhd_plus_sync_cmd_color;
	panel->videopanel = &visionox_r66451_fhd_plus_sync_cmd_video_panel;
	panel->commandpanel = &visionox_r66451_fhd_plus_sync_cmd_command_panel;
	panel->state = &visionox_r66451_fhd_plus_sync_cmd_state;
	panel->laneconfig = &visionox_r66451_fhd_plus_sync_cmd_lane_config;
	panel->paneltiminginfo = &visionox_r66451_fhd_plus_sync_cmd_timing_info;
	panel->panelresetseq = &visionox_r66451_fhd_plus_sync_cmd_reset_seq;
	panel->backlightinfo = &visionox_r66451_fhd_plus_sync_cmd_backlight;
	pinfo->mipi.panel_on_cmds = visionox_r66451_fhd_plus_sync_cmd_on_command;
	pinfo->mipi.panel_off_cmds = visionox_r66451_fhd_plus_sync_cmd_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(visionox_r66451_fhd_plus_sync_cmd_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(visionox_r66451_fhd_plus_sync_cmd_off_command);
	memcpy(phy_db->timing, visionox_r66451_fhd_plus_sync_cmd_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_VISIONOX_R66451_FHD_PLUS_SYNC_CMD_H_ */
