// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sim_sec_mode = {
	.clock = (720 + 120 + 12 + 60) * (1280 + 12 + 2 + 2) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 120,
	.hsync_end = 720 + 120 + 12,
	.htotal = 720 + 120 + 12 + 60,
	.vdisplay = 1280,
	.vsync_start = 1280 + 12,
	.vsync_end = 1280 + 12 + 2,
	.vtotal = 1280 + 12 + 2 + 2,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sim_sec = {
	.desc = {
		.modes = &sim_sec_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_CLOCK_NON_CONTINUOUS |
		 MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
