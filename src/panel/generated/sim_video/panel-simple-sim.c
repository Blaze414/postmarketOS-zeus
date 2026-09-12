// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sim_mode = {
	.clock = (640 + 8 + 8 + 8) * (480 + 6 + 2 + 6) * 60 / 1000,
	.hdisplay = 640,
	.hsync_start = 640 + 8,
	.hsync_end = 640 + 8 + 8,
	.htotal = 640 + 8 + 8 + 8,
	.vdisplay = 480,
	.vsync_start = 480 + 6,
	.vsync_end = 480 + 6 + 2,
	.vtotal = 480 + 6 + 2 + 6,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sim = {
	.desc = {
		.modes = &sim_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
