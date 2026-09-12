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

struct sy103_1280p_90hz {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct sy103_1280p_90hz *to_sy103_1280p_90hz(struct drm_panel *panel)
{
	return container_of_const(panel, struct sy103_1280p_90hz, panel);
}

static void sy103_1280p_90hz_reset(struct sy103_1280p_90hz *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int sy103_1280p_90hz_on(struct sy103_1280p_90hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x29);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x01ff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x01, 0x40, 0x40, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81,
				     0x03, 0x03, 0x00, 0x10, 0x00, 0x2c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82,
				     0x03, 0x03, 0x00, 0x10, 0x00, 0x2c, 0x00);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x00, 0x04, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2,
				     0x00, 0x40, 0x03, 0xff, 0x03, 0xff, 0x00,
				     0x90, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbf, 0x37, 0xbe);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x5a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf9,
				     0x58, 0x5f, 0x66, 0x6d, 0x74, 0x7b, 0x82,
				     0x89, 0x90, 0x97, 0x9e, 0xa5, 0xac);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 100);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0xaa, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0xff);

	return dsi_ctx.accum_err;
}

static int sy103_1280p_90hz_off(struct sy103_1280p_90hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int sy103_1280p_90hz_prepare(struct drm_panel *panel)
{
	struct sy103_1280p_90hz *ctx = to_sy103_1280p_90hz(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	sy103_1280p_90hz_reset(ctx);

	ret = sy103_1280p_90hz_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int sy103_1280p_90hz_unprepare(struct drm_panel *panel)
{
	struct sy103_1280p_90hz *ctx = to_sy103_1280p_90hz(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = sy103_1280p_90hz_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

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

static int sy103_1280p_90hz_get_modes(struct drm_panel *panel,
				      struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &sy103_1280p_90hz_mode);
}

static const struct drm_panel_funcs sy103_1280p_90hz_panel_funcs = {
	.prepare = sy103_1280p_90hz_prepare,
	.unprepare = sy103_1280p_90hz_unprepare,
	.get_modes = sy103_1280p_90hz_get_modes,
};

static int sy103_1280p_90hz_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct sy103_1280p_90hz *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct sy103_1280p_90hz, panel,
				   &sy103_1280p_90hz_panel_funcs,
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

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void sy103_1280p_90hz_remove(struct mipi_dsi_device *dsi)
{
	struct sy103_1280p_90hz *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id sy103_1280p_90hz_of_match[] = {
	{ .compatible = "mdss,sy103-1280p-90hz" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, sy103_1280p_90hz_of_match);

static struct mipi_dsi_driver sy103_1280p_90hz_driver = {
	.probe = sy103_1280p_90hz_probe,
	.remove = sy103_1280p_90hz_remove,
	.driver = {
		.name = "panel-sy103-1280p-90hz",
		.of_match_table = sy103_1280p_90hz_of_match,
	},
};
module_mipi_dsi_driver(sy103_1280p_90hz_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for sy103 amoled video mode panel without DSC");
MODULE_LICENSE("GPL");
