// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode nt36672c_plus_90hz_mode = {
	.clock = (1080 + 76 + 12 + 80) * (2400 + 54 + 10 + 10) * 90 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 76,
	.hsync_end = 1080 + 76 + 12,
	.htotal = 1080 + 76 + 12 + 80,
	.vdisplay = 2400,
	.vsync_start = 2400 + 54,
	.vsync_end = 2400 + 54 + 10,
	.vtotal = 2400 + 54 + 10 + 10,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static const struct panel_desc_dsi nt36672c_plus_90hz = {
	.desc = {
		.modes = &nt36672c_plus_90hz_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 0,
			.height = 0,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
		 MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 3,
};
