// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode l2_38_0c_0a_dsc_mode = {
	.clock = (1440 + 32 + 16 + 32) * (3200 + 24 + 8 + 24) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 32,
	.hsync_end = 1440 + 32 + 16,
	.htotal = 1440 + 32 + 16 + 32,
	.vdisplay = 3200,
	.vsync_start = 3200 + 24,
	.vsync_end = 3200 + 24 + 8,
	.vtotal = 3200 + 24 + 8 + 24,
	.width_mm = 70,
	.height_mm = 156,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi l2_38_0c_0a_dsc = {
	.desc = {
		.modes = &l2_38_0c_0a_dsc_mode,
		.num_modes = 1,
		.bpc = 10,
		.size = {
			.width = 70,
			.height = 156,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_CLOCK_NON_CONTINUOUS |
		 MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
