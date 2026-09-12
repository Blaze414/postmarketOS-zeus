// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/display/drm_dsc.h>
#include <drm/display/drm_dsc_helper.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct vtdr6130_plus {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline struct vtdr6130_plus *to_vtdr6130_plus(struct drm_panel *panel)
{
	return container_of_const(panel, struct vtdr6130_plus, panel);
}

static void vtdr6130_plus_reset(struct vtdr6130_plus *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int vtdr6130_plus_on(struct vtdr6130_plus *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x01);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x20);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70,
				     0x12, 0x00, 0x00, 0xab, 0x30, 0x80, 0x09,
				     0x60, 0x04, 0x38, 0x00, 0x28, 0x02, 0x1c,
				     0x02, 0x1c, 0x02, 0x00, 0x02, 0x0e, 0x00,
				     0x20, 0x03, 0xdd, 0x00, 0x07, 0x00, 0x0c,
				     0x02, 0x77, 0x02, 0x8b, 0x18, 0x00, 0x10,
				     0xf0, 0x07, 0x10, 0x20, 0x00, 0x06, 0x0f,
				     0x0f, 0x33, 0x0e, 0x1c, 0x2a, 0x38, 0x46,
				     0x54, 0x62, 0x69, 0x70, 0x77, 0x79, 0x7b,
				     0x7d, 0x7e, 0x02, 0x02, 0x22, 0x00, 0x2a,
				     0x40, 0x2a, 0xbe, 0x3a, 0xfc, 0x3a, 0xfa,
				     0x3a, 0xf8, 0x3b, 0x38, 0x3b, 0x78, 0x3b,
				     0xb6, 0x4b, 0xb6, 0x4b, 0xf4, 0x4b, 0xf4,
				     0x6c, 0x34, 0x84, 0x74, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x01, 0x38, 0x00, 0x14, 0x00, 0x1c, 0x00,
				     0x01, 0x66, 0x00, 0x14, 0x00, 0x14, 0x00,
				     0x01, 0x66, 0x00, 0x14, 0x05, 0xcc, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xce,
				     0x09, 0x11, 0x09, 0x11, 0x08, 0xc1, 0x07,
				     0xfa, 0x05, 0xa4, 0x00, 0x3c, 0x00, 0x34,
				     0x00, 0x24, 0x00, 0x0c, 0x00, 0x0c, 0x04,
				     0x00, 0x35);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x03, 0x33);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x33, 0x00, 0x00, 0x00, 0x3e, 0x00,
				     0x00, 0x00, 0x3e, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09,
				     0x06, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0x00, 0x08, 0x09, 0x09, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc,
				     0x10, 0x00, 0x00, 0x06, 0x11, 0x09, 0x3b,
				     0x09, 0x47, 0x09, 0x47, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe,
				     0x10, 0x10, 0x00, 0x08, 0x22, 0x09, 0x19,
				     0x09, 0x25, 0x09, 0x25, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfa, 0x08, 0x08, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x51, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf8, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf4, 0x9a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);

	return dsi_ctx.accum_err;
}

static int vtdr6130_plus_off(struct vtdr6130_plus *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int vtdr6130_plus_prepare(struct drm_panel *panel)
{
	struct vtdr6130_plus *ctx = to_vtdr6130_plus(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	vtdr6130_plus_reset(ctx);

	ret = vtdr6130_plus_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	drm_dsc_pps_payload_pack(&pps, &ctx->dsc);

	ret = mipi_dsi_picture_parameter_set(ctx->dsi, &pps);
	if (ret < 0) {
		dev_err(panel->dev, "failed to transmit PPS: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_compression_mode(ctx->dsi, true);
	if (ret < 0) {
		dev_err(dev, "failed to enable compression mode: %d\n", ret);
		return ret;
	}

	msleep(28); /* TODO: Is this panel-dependent? */

	return 0;
}

static int vtdr6130_plus_unprepare(struct drm_panel *panel)
{
	struct vtdr6130_plus *ctx = to_vtdr6130_plus(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = vtdr6130_plus_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode vtdr6130_plus_mode = {
	.clock = (1080 + 20 + 2 + 20) * (2400 + 20 + 2 + 18) * 144 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 20,
	.hsync_end = 1080 + 20 + 2,
	.htotal = 1080 + 20 + 2 + 20,
	.vdisplay = 2400,
	.vsync_start = 2400 + 20,
	.vsync_end = 2400 + 20 + 2,
	.vtotal = 2400 + 20 + 2 + 18,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int vtdr6130_plus_get_modes(struct drm_panel *panel,
				   struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &vtdr6130_plus_mode);
}

static const struct drm_panel_funcs vtdr6130_plus_panel_funcs = {
	.prepare = vtdr6130_plus_prepare,
	.unprepare = vtdr6130_plus_unprepare,
	.get_modes = vtdr6130_plus_get_modes,
};

static int vtdr6130_plus_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct vtdr6130_plus *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct vtdr6130_plus, panel,
				   &vtdr6130_plus_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 1 */
	ctx->dsc.slice_height = 40;
	ctx->dsc.slice_width = 540;
	/*
	 * TODO: hdisplay should be read from the selected mode once
	 * it is passed back to drm_panel (in prepare?)
	 */
	WARN_ON(1080 % ctx->dsc.slice_width);
	ctx->dsc.slice_count = 1080 / ctx->dsc.slice_width;
	ctx->dsc.bits_per_component = 8;
	ctx->dsc.bits_per_pixel = 8 << 4; /* 4 fractional bits */
	ctx->dsc.block_pred_enable = true;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void vtdr6130_plus_remove(struct mipi_dsi_device *dsi)
{
	struct vtdr6130_plus *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id vtdr6130_plus_of_match[] = {
	{ .compatible = "mdss,vtdr6130-plus" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, vtdr6130_plus_of_match);

static struct mipi_dsi_driver vtdr6130_plus_driver = {
	.probe = vtdr6130_plus_probe,
	.remove = vtdr6130_plus_remove,
	.driver = {
		.name = "panel-vtdr6130-plus",
		.of_match_table = vtdr6130_plus_of_match,
	},
};
module_mipi_dsi_driver(vtdr6130_plus_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for vtdr6130 amoled video mode dsi visionox panel with DSC");
MODULE_LICENSE("GPL");
