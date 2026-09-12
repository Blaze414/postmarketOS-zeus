// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode r66451_plus_90hz_cphy_nodsc_mode = {
	.clock = (1080 + 96 + 32 + 40) * (2340 + 25 + 1 + 4) * 90 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 96,
	.hsync_end = 1080 + 96 + 32,
	.htotal = 1080 + 96 + 32 + 40,
	.vdisplay = 2340,
	.vsync_start = 2340 + 25,
	.vsync_end = 2340 + 25 + 1,
	.vtotal = 2340 + 25 + 1 + 4,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi r66451_plus_90hz_cphy_nodsc = {
	.desc = {
		.modes = &r66451_plus_90hz_cphy_nodsc_mode,
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
	.lanes = 3,
};
