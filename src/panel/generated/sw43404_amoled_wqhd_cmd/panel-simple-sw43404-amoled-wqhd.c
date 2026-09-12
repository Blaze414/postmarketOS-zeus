// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sw43404_amoled_wqhd_mode = {
	.clock = (1440 + 60 + 12 + 30) * (2880 + 8 + 1 + 8) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 60,
	.hsync_end = 1440 + 60 + 12,
	.htotal = 1440 + 60 + 12 + 30,
	.vdisplay = 2880,
	.vsync_start = 2880 + 8,
	.vsync_end = 2880 + 8 + 1,
	.vtotal = 2880 + 8 + 1 + 8,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi sw43404_amoled_wqhd = {
	.desc = {
		.modes = &sw43404_amoled_wqhd_mode,
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
