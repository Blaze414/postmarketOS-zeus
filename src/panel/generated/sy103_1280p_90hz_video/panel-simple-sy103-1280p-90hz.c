// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sy103_1280p_90hz_mode = {
	.clock = (1280 + 64 + 32 + 32) * (1280 + 44 + 2 + 14) * 90 / 1000,
	.hdisplay = 1280,
	.hsync_start = 1280 + 64,
	.hsync_end = 1280 + 64 + 32,
	.htotal = 1280 + 64 + 32 + 32,
	.vdisplay = 1280,
	.vsync_start = 1280 + 44,
	.vsync_end = 1280 + 44 + 2,
	.vtotal = 1280 + 44 + 2 + 14,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sy103_1280p_90hz = {
	.desc = {
		.modes = &sy103_1280p_90hz_mode,
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
