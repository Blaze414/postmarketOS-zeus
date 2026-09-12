// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sim_mode = {
	.clock = (1440 + 120 + 40 + 100) * (2560 + 100 + 40 + 100) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 120,
	.hsync_end = 1440 + 120 + 40,
	.htotal = 1440 + 120 + 40 + 100,
	.vdisplay = 2560,
	.vsync_start = 2560 + 100,
	.vsync_end = 2560 + 100 + 40,
	.vtotal = 2560 + 100 + 40 + 100,
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
	.flags = MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
