// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct sim_sec {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline struct sim_sec *to_sim_sec(struct drm_panel *panel)
{
	return container_of_const(panel, struct sim_sec, panel);
}

static void sim_sec_reset(struct sim_sec *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int sim_sec_on(struct sim_sec *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_nop_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 240);

	return dsi_ctx.accum_err;
}

static int sim_sec_off(struct sim_sec *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int sim_sec_prepare(struct drm_panel *panel)
{
	struct sim_sec *ctx = to_sim_sec(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	sim_sec_reset(ctx);

	ret = sim_sec_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int sim_sec_unprepare(struct drm_panel *panel)
{
	struct sim_sec *ctx = to_sim_sec(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = sim_sec_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode sim_sec_mode = {
	.clock = (720 + 120 + 12 + 60) * (1280 + 12 + 2 + 2) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 120,
	.hsync_end = 720 + 120 + 12,
	.htotal = 720 + 120 + 12 + 60,
	.vdisplay = 1280,
	.vsync_start = 1280 + 12,
	.vsync_end = 1280 + 12 + 2,
	.vtotal = 1280 + 12 + 2 + 2,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int sim_sec_get_modes(struct drm_panel *panel,
			     struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &sim_sec_mode);
}

static const struct drm_panel_funcs sim_sec_panel_funcs = {
	.prepare = sim_sec_prepare,
	.unprepare = sim_sec_unprepare,
	.get_modes = sim_sec_get_modes,
};

static int sim_sec_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness_large(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

// TODO: Check if /sys/class/backlight/.../actual_brightness actually returns
// correct values. If not, remove this function.
static int sim_sec_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness_large(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness;
}

static const struct backlight_ops sim_sec_bl_ops = {
	.update_status = sim_sec_bl_update_status,
	.get_brightness = sim_sec_bl_get_brightness,
};

static struct backlight_device *
sim_sec_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 1023,
		.max_brightness = 1023,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &sim_sec_bl_ops, &props);
}

static int sim_sec_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct sim_sec *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct sim_sec, panel,
				   &sim_sec_panel_funcs,
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
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = sim_sec_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void sim_sec_remove(struct mipi_dsi_device *dsi)
{
	struct sim_sec *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id sim_sec_of_match[] = {
	{ .compatible = "sim,sec" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, sim_sec_of_match);

static struct mipi_dsi_driver sim_sec_driver = {
	.probe = sim_sec_probe,
	.remove = sim_sec_remove,
	.driver = {
		.name = "panel-sim-sec",
		.of_match_table = sim_sec_of_match,
	},
};
module_mipi_dsi_driver(sim_sec_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for sim hd command mode secondary dsi panel");
MODULE_LICENSE("GPL");
