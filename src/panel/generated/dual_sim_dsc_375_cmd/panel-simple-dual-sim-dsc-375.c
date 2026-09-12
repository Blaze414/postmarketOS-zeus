// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode dual_sim_dsc_375_mode = {
	.clock = (1080 + 30 + 4 + 100) * (3840 + 8 + 1 + 7) * 30 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 30,
	.hsync_end = 1080 + 30 + 4,
	.htotal = 1080 + 30 + 4 + 100,
	.vdisplay = 3840,
	.vsync_start = 3840 + 8,
	.vsync_end = 3840 + 8 + 1,
	.vtotal = 3840 + 8 + 1 + 7,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi dual_sim_dsc_375 = {
	.desc = {
		.modes = &dual_sim_dsc_375_mode,
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
