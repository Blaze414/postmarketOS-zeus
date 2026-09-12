// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sy103_dsc_2544p_75hz_mode = {
	.clock = (2544 + 64 + 32 + 32) * (2544 + 44 + 2 + 14) * 75 / 1000,
	.hdisplay = 2544,
	.hsync_start = 2544 + 64,
	.hsync_end = 2544 + 64 + 32,
	.htotal = 2544 + 64 + 32 + 32,
	.vdisplay = 2544,
	.vsync_start = 2544 + 44,
	.vsync_end = 2544 + 44 + 2,
	.vtotal = 2544 + 44 + 2 + 14,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sy103_dsc_2544p_75hz = {
	.desc = {
		.modes = &sy103_dsc_2544p_75hz_mode,
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
