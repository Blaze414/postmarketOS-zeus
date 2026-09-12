// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_RM69299_VISIONOX_AMOLED_VIDEO_H_
#define _PANEL_RM69299_VISIONOX_AMOLED_VIDEO_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config rm69299_visionox_amoled_video_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_rm69299_visionox_amoled_video",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 0,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 1,
	.panel_init_delay = 0,
};

static struct panel_resolution rm69299_visionox_amoled_video_panel_res = {
	.panel_width = 1080,
	.panel_height = 2248,
	.hfront_porch = 26,
	.hback_porch = 36,
	.hpulse_width = 2,
	.hsync_skew = 0,
	.vfront_porch = 56,
	.vback_porch = 4,
	.vpulse_width = 4,
	/* Borders not supported yet */
};

static struct color_info rm69299_visionox_amoled_video_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char rm69299_visionox_amoled_video_on_cmd_0[] = {
	0x02, 0x00, 0x39, 0xc0, 0xfe, 0x00, 0xff, 0xff
};
static char rm69299_visionox_amoled_video_on_cmd_1[] = {
	0x02, 0x00, 0x39, 0xc0, 0xc2, 0x08, 0xff, 0xff
};
static char rm69299_visionox_amoled_video_on_cmd_2[] = {
	0x02, 0x00, 0x39, 0xc0, 0x35, 0x00, 0xff, 0xff
};
static char rm69299_visionox_amoled_video_on_cmd_3[] = {
	0x02, 0x00, 0x39, 0xc0, 0x51, 0xff, 0xff, 0xff
};
static char rm69299_visionox_amoled_video_on_cmd_4[] = {
	0x11, 0x00, 0x05, 0x80
};
static char rm69299_visionox_amoled_video_on_cmd_5[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd rm69299_visionox_amoled_video_on_command[] = {
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_0), rm69299_visionox_amoled_video_on_cmd_0, 0 },
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_1), rm69299_visionox_amoled_video_on_cmd_1, 0 },
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_2), rm69299_visionox_amoled_video_on_cmd_2, 0 },
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_3), rm69299_visionox_amoled_video_on_cmd_3, 0 },
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_4), rm69299_visionox_amoled_video_on_cmd_4, 150 },
	{ sizeof(rm69299_visionox_amoled_video_on_cmd_5), rm69299_visionox_amoled_video_on_cmd_5, 50 },
};

static char rm69299_visionox_amoled_video_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char rm69299_visionox_amoled_video_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd rm69299_visionox_amoled_video_off_command[] = {
	{ sizeof(rm69299_visionox_amoled_video_off_cmd_0), rm69299_visionox_amoled_video_off_cmd_0, 50 },
	{ sizeof(rm69299_visionox_amoled_video_off_cmd_1), rm69299_visionox_amoled_video_off_cmd_1, 150 },
};

static struct command_state rm69299_visionox_amoled_video_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info rm69299_visionox_amoled_video_command_panel = {
	/* Unused, this is a video mode panel */
};

static struct videopanel_info rm69299_visionox_amoled_video_video_panel = {
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

static struct lane_configuration rm69299_visionox_amoled_video_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t rm69299_visionox_amoled_video_timings[] = {
	
};

static struct panel_timing rm69299_visionox_amoled_video_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence rm69299_visionox_amoled_video_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static inline void panel_rm69299_visionox_amoled_video_select(struct panel_struct *panel,
							      struct msm_panel_info *pinfo,
							      struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &rm69299_visionox_amoled_video_panel_data;
	panel->panelres = &rm69299_visionox_amoled_video_panel_res;
	panel->color = &rm69299_visionox_amoled_video_color;
	panel->videopanel = &rm69299_visionox_amoled_video_video_panel;
	panel->commandpanel = &rm69299_visionox_amoled_video_command_panel;
	panel->state = &rm69299_visionox_amoled_video_state;
	panel->laneconfig = &rm69299_visionox_amoled_video_lane_config;
	panel->paneltiminginfo = &rm69299_visionox_amoled_video_timing_info;
	panel->panelresetseq = &rm69299_visionox_amoled_video_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = rm69299_visionox_amoled_video_on_command;
	pinfo->mipi.panel_off_cmds = rm69299_visionox_amoled_video_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(rm69299_visionox_amoled_video_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(rm69299_visionox_amoled_video_off_command);
	memcpy(phy_db->timing, rm69299_visionox_amoled_video_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_RM69299_VISIONOX_AMOLED_VIDEO_H_ */
