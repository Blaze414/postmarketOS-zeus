// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_SY103_DUAL_DSC_2544P_75HZ_VIDEO_H_
#define _PANEL_SY103_DUAL_DSC_2544P_75HZ_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config sy103_dual_dsc_2544p_75hz_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_sy103_dual_dsc_2544p_75hz_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 75,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution sy103_dual_dsc_2544p_75hz_video_panel_res = {
	.panel_width = 1272,
	.panel_height = 2544,
	.hfront_porch = 64,
	.hback_porch = 32,
	.hpulse_width = 32,
	.hsync_skew = 0,
	.vfront_porch = 44,
	.vback_porch = 14,
	.vpulse_width = 2,
	/* Borders not supported yet */
};

static struct color_info sy103_dual_dsc_2544p_75hz_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char sy103_dual_dsc_2544p_75hz_video_on_cmd_0[] = {
	0x03, 0x81, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_1[] = {
	0x53, 0x29, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_2[] = {
	0x03, 0x00, 0x39, 0xc0, 0x51, 0xff, 0x01, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_3[] = {
	0x69, 0x00, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_4[] = {
	0x6b, 0x10, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_5[] = {
	0x2d, 0x00, 0x39, 0xc0, 0x70, 0x11, 0x00, 0x00,
	0x89, 0x30, 0x80, 0x09, 0xf0, 0x04, 0xf8, 0x00,
	0x20, 0x04, 0xf8, 0x04, 0xf8, 0x02, 0x00, 0x03,
	0x7c, 0x00, 0x20, 0x03, 0x59, 0x00, 0x11, 0x00,
	0x0c, 0x03, 0x19, 0x01, 0x5a, 0x18, 0x00, 0x10,
	0xf0, 0x03, 0x0c, 0x20, 0x00, 0x06, 0x0b, 0x0b,
	0x33, 0xff, 0xff, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_6[] = {
	0x05, 0x00, 0x39, 0xc0, 0x80, 0x01, 0x3e, 0x3e,
	0x11, 0xff, 0xff, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_7[] = {
	0x08, 0x00, 0x39, 0xc0, 0x81, 0x01, 0xdc, 0x00,
	0x10, 0x00, 0x2c, 0x00
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_8[] = {
	0x08, 0x00, 0x39, 0xc0, 0x82, 0x01, 0xdc, 0x00,
	0x10, 0x00, 0x2c, 0x00
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_9[] = {
	0x35, 0x00, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_10[] = {
	0x25, 0x01, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_11[] = {
	0x03, 0x00, 0x39, 0xc0, 0x2a, 0x00, 0x08, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_12[] = {
	0x03, 0x00, 0x39, 0xc0, 0x2b, 0x00, 0x08, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_13[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x11, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_14[] = {
	0x04, 0x00, 0x39, 0xc0, 0xc0, 0x00, 0x04, 0x00
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_15[] = {
	0x0a, 0x00, 0x39, 0xc0, 0xc2, 0x01, 0x50, 0x01,
	0x50, 0x01, 0x50, 0x00, 0x90, 0x02, 0xff, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_16[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x12, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_17[] = {
	0xd3, 0x20, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_18[] = {
	0x03, 0x00, 0x39, 0xc0, 0xbf, 0x37, 0xbe, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_19[] = {
	0x03, 0x00, 0x39, 0xc0, 0xff, 0x5a, 0x81, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_20[] = {
	0x65, 0x0b, 0x15, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_21[] = {
	0x0e, 0x00, 0x39, 0xc0, 0xf9, 0x58, 0x5f, 0x66,
	0x6d, 0x74, 0x7b, 0x82, 0x89, 0x90, 0x97, 0x9e,
	0xa5, 0xac, 0xff, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_22[] = {
	0x11, 0x00, 0x05, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_23[] = {
	0x29, 0x00, 0x05, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_24[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xaa, 0x11, 0xff
};
static char sy103_dual_dsc_2544p_75hz_video_on_cmd_25[] = {
	0xc0, 0xff, 0x15, 0x80
};

static struct mipi_dsi_cmd sy103_dual_dsc_2544p_75hz_video_on_command[] = {
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_0), sy103_dual_dsc_2544p_75hz_video_on_cmd_0, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_1), sy103_dual_dsc_2544p_75hz_video_on_cmd_1, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_2), sy103_dual_dsc_2544p_75hz_video_on_cmd_2, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_3), sy103_dual_dsc_2544p_75hz_video_on_cmd_3, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_4), sy103_dual_dsc_2544p_75hz_video_on_cmd_4, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_5), sy103_dual_dsc_2544p_75hz_video_on_cmd_5, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_6), sy103_dual_dsc_2544p_75hz_video_on_cmd_6, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_7), sy103_dual_dsc_2544p_75hz_video_on_cmd_7, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_8), sy103_dual_dsc_2544p_75hz_video_on_cmd_8, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_9), sy103_dual_dsc_2544p_75hz_video_on_cmd_9, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_10), sy103_dual_dsc_2544p_75hz_video_on_cmd_10, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_11), sy103_dual_dsc_2544p_75hz_video_on_cmd_11, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_12), sy103_dual_dsc_2544p_75hz_video_on_cmd_12, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_13), sy103_dual_dsc_2544p_75hz_video_on_cmd_13, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_14), sy103_dual_dsc_2544p_75hz_video_on_cmd_14, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_15), sy103_dual_dsc_2544p_75hz_video_on_cmd_15, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_16), sy103_dual_dsc_2544p_75hz_video_on_cmd_16, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_17), sy103_dual_dsc_2544p_75hz_video_on_cmd_17, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_18), sy103_dual_dsc_2544p_75hz_video_on_cmd_18, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_19), sy103_dual_dsc_2544p_75hz_video_on_cmd_19, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_20), sy103_dual_dsc_2544p_75hz_video_on_cmd_20, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_21), sy103_dual_dsc_2544p_75hz_video_on_cmd_21, 20 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_22), sy103_dual_dsc_2544p_75hz_video_on_cmd_22, 100 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_23), sy103_dual_dsc_2544p_75hz_video_on_cmd_23, 20 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_24), sy103_dual_dsc_2544p_75hz_video_on_cmd_24, 0 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_on_cmd_25), sy103_dual_dsc_2544p_75hz_video_on_cmd_25, 0 },
};

static char sy103_dual_dsc_2544p_75hz_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char sy103_dual_dsc_2544p_75hz_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd sy103_dual_dsc_2544p_75hz_video_off_command[] = {
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_off_cmd_0), sy103_dual_dsc_2544p_75hz_video_off_cmd_0, 20 },
	{ sizeof(sy103_dual_dsc_2544p_75hz_video_off_cmd_1), sy103_dual_dsc_2544p_75hz_video_off_cmd_1, 120 },
};

static struct command_state sy103_dual_dsc_2544p_75hz_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info sy103_dual_dsc_2544p_75hz_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info sy103_dual_dsc_2544p_75hz_video_video_panel = {
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

static struct lane_configuration sy103_dual_dsc_2544p_75hz_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t sy103_dual_dsc_2544p_75hz_video_timings[] = {
	
};

static struct panel_timing sy103_dual_dsc_2544p_75hz_video_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence sy103_dual_dsc_2544p_75hz_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 20 },
	.pin_direction = 2,
};

static inline void panel_sy103_dual_dsc_2544p_75hz_video_select(struct panel_struct *panel,
								struct msm_panel_info *pinfo,
								struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &sy103_dual_dsc_2544p_75hz_video_panel_data;
	panel->panelres = &sy103_dual_dsc_2544p_75hz_video_panel_res;
	panel->color = &sy103_dual_dsc_2544p_75hz_video_color;
	panel->videopanel = &sy103_dual_dsc_2544p_75hz_video_video_panel;
	panel->commandpanel = &sy103_dual_dsc_2544p_75hz_video_command_panel;
	panel->state = &sy103_dual_dsc_2544p_75hz_video_state;
	panel->laneconfig = &sy103_dual_dsc_2544p_75hz_video_lane_config;
	panel->paneltiminginfo = &sy103_dual_dsc_2544p_75hz_video_timing_info;
	panel->panelresetseq = &sy103_dual_dsc_2544p_75hz_video_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = sy103_dual_dsc_2544p_75hz_video_on_command;
	pinfo->mipi.panel_off_cmds = sy103_dual_dsc_2544p_75hz_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(sy103_dual_dsc_2544p_75hz_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(sy103_dual_dsc_2544p_75hz_video_off_command);
	memcpy(phy_db->timing, sy103_dual_dsc_2544p_75hz_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_SY103_DUAL_DSC_2544P_75HZ_VIDEO_H_ */
