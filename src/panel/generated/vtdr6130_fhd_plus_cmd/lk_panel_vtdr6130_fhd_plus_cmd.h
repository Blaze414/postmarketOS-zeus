// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_VTDR6130_FHD_PLUS_CMD_H_
#define _PANEL_VTDR6130_FHD_PLUS_CMD_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config vtdr6130_fhd_plus_cmd_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_vtdr6130_fhd_plus_cmd",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 1,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 144,
	.panel_lp11_init = 0,
	.panel_init_delay = 0,
};

static struct panel_resolution vtdr6130_fhd_plus_cmd_panel_res = {
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

static struct color_info vtdr6130_fhd_plus_cmd_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};


static struct mipi_dsi_cmd vtdr6130_fhd_plus_cmd_on_command[] = {
};

static char vtdr6130_fhd_plus_cmd_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char vtdr6130_fhd_plus_cmd_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd vtdr6130_fhd_plus_cmd_off_command[] = {
	{ sizeof(vtdr6130_fhd_plus_cmd_off_cmd_0), vtdr6130_fhd_plus_cmd_off_cmd_0, 20 },
	{ sizeof(vtdr6130_fhd_plus_cmd_off_cmd_1), vtdr6130_fhd_plus_cmd_off_cmd_1, 120 },
};

static struct command_state vtdr6130_fhd_plus_cmd_state = {
	.oncommand_state = 0,
	.offcommand_state = 1,
};

static struct commandpanel_info vtdr6130_fhd_plus_cmd_command_panel = {
	/* FIXME: This is a command mode panel */
};

static struct videopanel_info vtdr6130_fhd_plus_cmd_video_panel = {
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

static struct lane_configuration vtdr6130_fhd_plus_cmd_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t vtdr6130_fhd_plus_cmd_timings[] = {
	
};

static struct panel_timing vtdr6130_fhd_plus_cmd_timing_info = {
	.tclk_post = 0x00,
	.tclk_pre = 0x00,
};

static struct panel_reset_sequence vtdr6130_fhd_plus_cmd_reset_seq = {
	.pin_state = { 1, 0, 1 },
	.sleep = { 10, 10, 10 },
	.pin_direction = 2,
};

static inline void panel_vtdr6130_fhd_plus_cmd_select(struct panel_struct *panel,
						      struct msm_panel_info *pinfo,
						      struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &vtdr6130_fhd_plus_cmd_panel_data;
	panel->panelres = &vtdr6130_fhd_plus_cmd_panel_res;
	panel->color = &vtdr6130_fhd_plus_cmd_color;
	panel->videopanel = &vtdr6130_fhd_plus_cmd_video_panel;
	panel->commandpanel = &vtdr6130_fhd_plus_cmd_command_panel;
	panel->state = &vtdr6130_fhd_plus_cmd_state;
	panel->laneconfig = &vtdr6130_fhd_plus_cmd_lane_config;
	panel->paneltiminginfo = &vtdr6130_fhd_plus_cmd_timing_info;
	panel->panelresetseq = &vtdr6130_fhd_plus_cmd_reset_seq;
	panel->backlightinfo = NULL;
	pinfo->mipi.panel_on_cmds = vtdr6130_fhd_plus_cmd_on_command;
	pinfo->mipi.panel_off_cmds = vtdr6130_fhd_plus_cmd_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(vtdr6130_fhd_plus_cmd_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(vtdr6130_fhd_plus_cmd_off_command);
	memcpy(phy_db->timing, vtdr6130_fhd_plus_cmd_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_VTDR6130_FHD_PLUS_CMD_H_ */
