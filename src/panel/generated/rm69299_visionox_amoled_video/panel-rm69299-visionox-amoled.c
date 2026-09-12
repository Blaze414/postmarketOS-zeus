// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct rm69299_visionox_amoled {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct rm69299_visionox_amoled *to_rm69299_visionox_amoled(struct drm_panel *panel)
{
	return container_of_const(panel, struct rm69299_visionox_amoled, panel);
}

static void rm69299_visionox_amoled_reset(struct rm69299_visionox_amoled *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int rm69299_visionox_amoled_on(struct rm69299_visionox_amoled *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfe, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x08);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x00ff);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);

	return dsi_ctx.accum_err;
}

static int rm69299_visionox_amoled_off(struct rm69299_visionox_amoled *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);

	return dsi_ctx.accum_err;
}

static int rm69299_visionox_amoled_prepare(struct drm_panel *panel)
{
	struct rm69299_visionox_amoled *ctx = to_rm69299_visionox_amoled(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	rm69299_visionox_amoled_reset(ctx);

	ret = rm69299_visionox_amoled_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int rm69299_visionox_amoled_unprepare(struct drm_panel *panel)
{
	struct rm69299_visionox_amoled *ctx = to_rm69299_visionox_amoled(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = rm69299_visionox_amoled_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode rm69299_visionox_amoled_mode = {
	.clock = (1080 + 26 + 2 + 36) * (2248 + 56 + 4 + 4) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 26,
	.hsync_end = 1080 + 26 + 2,
	.htotal = 1080 + 26 + 2 + 36,
	.vdisplay = 2248,
	.vsync_start = 2248 + 56,
	.vsync_end = 2248 + 56 + 4,
	.vtotal = 2248 + 56 + 4 + 4,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int rm69299_visionox_amoled_get_modes(struct drm_panel *panel,
					     struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &rm69299_visionox_amoled_mode);
}

static const struct drm_panel_funcs rm69299_visionox_amoled_panel_funcs = {
	.prepare = rm69299_visionox_amoled_prepare,
	.unprepare = rm69299_visionox_amoled_unprepare,
	.get_modes = rm69299_visionox_amoled_get_modes,
};

static int rm69299_visionox_amoled_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct rm69299_visionox_amoled *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct rm69299_visionox_amoled, panel,
				   &rm69299_visionox_amoled_panel_funcs,
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
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void rm69299_visionox_amoled_remove(struct mipi_dsi_device *dsi)
{
	struct rm69299_visionox_amoled *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id rm69299_visionox_amoled_of_match[] = {
	{ .compatible = "mdss,rm69299-visionox-amoled" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, rm69299_visionox_amoled_of_match);

static struct mipi_dsi_driver rm69299_visionox_amoled_driver = {
	.probe = rm69299_visionox_amoled_probe,
	.remove = rm69299_visionox_amoled_remove,
	.driver = {
		.name = "panel-rm69299-visionox-amoled",
		.of_match_table = rm69299_visionox_amoled_of_match,
	},
};
module_mipi_dsi_driver(rm69299_visionox_amoled_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for rm69299 amoled fhd+ video mode dsi visionox panel");
MODULE_LICENSE("GPL");
