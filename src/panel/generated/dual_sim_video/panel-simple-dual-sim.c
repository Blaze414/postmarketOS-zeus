// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode dual_sim_mode = {
	.clock = (1280 + 120 + 16 + 44) * (1440 + 8 + 4 + 4) * 60 / 1000,
	.hdisplay = 1280,
	.hsync_start = 1280 + 120,
	.hsync_end = 1280 + 120 + 16,
	.htotal = 1280 + 120 + 16 + 44,
	.vdisplay = 1440,
	.vsync_start = 1440 + 8,
	.vsync_end = 1440 + 8 + 4,
	.vtotal = 1440 + 8 + 4 + 4,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi dual_sim = {
	.desc = {
		.modes = &dual_sim_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
