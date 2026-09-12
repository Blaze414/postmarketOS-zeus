// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode dual_sim_mode = {
	.clock = (540 + 28 + 4 + 4) * (1920 + 12 + 2 + 12) * 120 / 1000,
	.hdisplay = 540,
	.hsync_start = 540 + 28,
	.hsync_end = 540 + 28 + 4,
	.htotal = 540 + 28 + 4 + 4,
	.vdisplay = 1920,
	.vsync_start = 1920 + 12,
	.vsync_end = 1920 + 12 + 2,
	.vtotal = 1920 + 12 + 2 + 12,
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
	.flags = MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
