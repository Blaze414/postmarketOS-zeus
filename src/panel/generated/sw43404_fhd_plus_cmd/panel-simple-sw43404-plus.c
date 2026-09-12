// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sw43404_plus_mode = {
	.clock = (1080 + 160 + 16 + 72) * (2160 + 8 + 1 + 8) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 160,
	.hsync_end = 1080 + 160 + 16,
	.htotal = 1080 + 160 + 16 + 72,
	.vdisplay = 2160,
	.vsync_start = 2160 + 8,
	.vsync_end = 2160 + 8 + 1,
	.vtotal = 2160 + 8 + 1 + 8,
	.width_mm = 68,
	.height_mm = 138,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sw43404_plus = {
	.desc = {
		.modes = &sw43404_plus_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 68,
			.height = 138,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_NO_EOT_PACKET | MIPI_DSI_CLOCK_NON_CONTINUOUS,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
