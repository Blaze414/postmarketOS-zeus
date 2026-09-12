// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode nt35695b_truly_mode = {
	.clock = (1080 + 120 + 12 + 60) * (1920 + 12 + 2 + 2) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 120,
	.hsync_end = 1080 + 120 + 12,
	.htotal = 1080 + 120 + 12 + 60,
	.vdisplay = 1920,
	.vsync_start = 1920 + 12,
	.vsync_end = 1920 + 12 + 2,
	.vtotal = 1920 + 12 + 2 + 2,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi nt35695b_truly = {
	.desc = {
		.modes = &nt35695b_truly_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
