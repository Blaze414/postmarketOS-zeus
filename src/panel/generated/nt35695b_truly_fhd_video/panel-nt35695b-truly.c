// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct nt35695b_truly {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline struct nt35695b_truly *to_nt35695b_truly(struct drm_panel *panel)
{
	return container_of_const(panel, struct nt35695b_truly, panel);
}

static void nt35695b_truly_reset(struct nt35695b_truly *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int nt35695b_truly_on(struct nt35695b_truly *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_usleep_range(&dsi_ctx, 16000, 17000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0xa8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0xad);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0xaa);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0xaa);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0xb0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0xb3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x4a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x6d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0xd8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4b, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4c, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x50, 0x10);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x0000);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x43);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0xd8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x93, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x94, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbf, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x6d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xec, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x03);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int nt35695b_truly_off(struct nt35695b_truly *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int nt35695b_truly_prepare(struct drm_panel *panel)
{
	struct nt35695b_truly *ctx = to_nt35695b_truly(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	nt35695b_truly_reset(ctx);

	ret = nt35695b_truly_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int nt35695b_truly_unprepare(struct drm_panel *panel)
{
	struct nt35695b_truly *ctx = to_nt35695b_truly(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = nt35695b_truly_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode nt35695b_truly_mode = {
	.clock = (1080 + 120 + 12 + 60) * (1920 + 12 + 2 + 2) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 120,
	.hsync_end = 1080 + 120 + 12,
	.htotal = 1080 + 120 + 12 + 60,
	.vdisplay = 1920,
	.vsync_start = 1920 + 12,
	.vsync_end = 1920 + 12 + 2,
	.vtotal = 1920 + 12 + 2 + 2,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int nt35695b_truly_get_modes(struct drm_panel *panel,
				    struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &nt35695b_truly_mode);
}

static const struct drm_panel_funcs nt35695b_truly_panel_funcs = {
	.prepare = nt35695b_truly_prepare,
	.unprepare = nt35695b_truly_unprepare,
	.get_modes = nt35695b_truly_get_modes,
};

static int nt35695b_truly_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt35695b_truly *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct nt35695b_truly, panel,
				   &nt35695b_truly_panel_funcs,
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
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void nt35695b_truly_remove(struct mipi_dsi_device *dsi)
{
	struct nt35695b_truly *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id nt35695b_truly_of_match[] = {
	{ .compatible = "mdss,nt35695b-truly" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt35695b_truly_of_match);

static struct mipi_dsi_driver nt35695b_truly_driver = {
	.probe = nt35695b_truly_probe,
	.remove = nt35695b_truly_remove,
	.driver = {
		.name = "panel-nt35695b-truly",
		.of_match_table = nt35695b_truly_of_match,
	},
};
module_mipi_dsi_driver(nt35695b_truly_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for nt35695b truly fhd video mode dsi panel");
MODULE_LICENSE("GPL");
