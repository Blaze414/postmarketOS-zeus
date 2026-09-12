// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode nt36672e_plus_120_mode = {
	.clock = (1080 + 80 + 12 + 60) * (2408 + 46 + 10 + 10) * 120 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 80,
	.hsync_end = 1080 + 80 + 12,
	.htotal = 1080 + 80 + 12 + 60,
	.vdisplay = 2408,
	.vsync_start = 2408 + 46,
	.vsync_end = 2408 + 46 + 10,
	.vtotal = 2408 + 46 + 10 + 10,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi nt36672e_plus_120 = {
	.desc = {
		.modes = &nt36672e_plus_120_mode,
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
