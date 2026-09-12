// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <drm/display/drm_dsc.h>
#include <drm/display/drm_dsc_helper.h>
#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct r66451_plus_cphy_144hz {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline
struct r66451_plus_cphy_144hz *to_r66451_plus_cphy_144hz(struct drm_panel *panel)
{
	return container_of_const(panel, struct r66451_plus_cphy_144hz, panel);
}

static void r66451_plus_cphy_144hz_reset(struct r66451_plus_cphy_144hz *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int r66451_plus_cphy_144hz_on(struct r66451_plus_cphy_144hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x00, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x20, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x6c, 0x00, 0x06, 0x23, 0xaf, 0x13, 0x1a,
				     0x05, 0x04, 0xfa, 0x05, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x10, 0x00, 0x00, 0x02, 0x00, 0x00,
				     0x00, 0x29, 0x00, 0x01, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x22, 0x00, 0x00, 0x00, 0x00, 0x11,
				     0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00,
				     0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf,
				     0x64, 0x0b, 0x00, 0x22, 0x00, 0xcd, 0x03,
				     0x33, 0x04, 0x00, 0x0b, 0x77, 0x01, 0x01,
				     0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04,
				     0x04, 0x04, 0x05, 0x00, 0x00, 0x00, 0x3b,
				     0x00, 0x3b, 0x01, 0x64, 0x01, 0x64, 0x01,
				     0x64, 0x01, 0x64, 0x01, 0x64, 0x01, 0x64,
				     0x03, 0xff, 0x03, 0xff, 0x03, 0xff, 0x00,
				     0x00, 0x00, 0x3b, 0x00, 0x3b, 0x01, 0x64,
				     0x01, 0x64, 0x01, 0x64, 0x01, 0x64, 0x01,
				     0x64, 0x01, 0x64, 0x03, 0xff, 0x03, 0xff,
				     0x03, 0xff, 0x01, 0x62, 0x01, 0x62, 0x01,
				     0x62, 0x01, 0x62, 0x01, 0x62, 0x01, 0x62,
				     0x01, 0x62, 0x01, 0x62, 0x01, 0x62, 0x01,
				     0x62, 0x01, 0x62, 0x01, 0x62, 0x19, 0x19,
				     0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
				     0x19, 0x19, 0x19, 0x00, 0x00, 0x00, 0x43,
				     0x00, 0x43, 0x01, 0x98, 0x01, 0x98, 0x06,
				     0x61, 0x06, 0x61, 0x0f, 0xf6, 0x0f, 0xf6,
				     0x0f, 0xf6, 0x0f, 0xf6, 0x0f, 0xf6, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0,
				     0x44, 0x44, 0xb2, 0x28, 0x00, 0x28, 0x5a,
				     0x00, 0x5a, 0x03, 0x0d, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1,
				     0x05, 0x00, 0x21, 0x02, 0x24, 0x19, 0x24,
				     0x2d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3,
				     0x49, 0x00, 0x00, 0x01, 0x1a, 0x15, 0x00,
				     0x15, 0x07, 0x0f, 0x77, 0x77, 0x77, 0x37,
				     0xb2, 0x11, 0x00, 0xa0, 0x3c, 0x9a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7,
				     0x00, 0xb9, 0x34, 0x00, 0x40, 0x04, 0x00,
				     0xf0, 0x0f, 0x00, 0x40, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x19, 0x34, 0x00, 0x40,
				     0x04, 0x00, 0xf0, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x30, 0x00, 0x30, 0x00, 0x30,
				     0x00, 0x30, 0x00, 0x30, 0x05, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x0f, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x0f, 0x00, 0x2f, 0x00, 0x0f,
				     0x00, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf,
				     0x50, 0x42, 0x58, 0x81, 0x2d, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x6b, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				     0x0f, 0xff, 0xd4, 0x0e, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x0f, 0x53, 0x18, 0x00,
				     0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x8b, 0x8b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf7, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4,
				     0x34, 0xb4, 0x00, 0x00, 0x00, 0x30, 0x04,
				     0x0c, 0xe2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x50, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3,
				     0x50, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf2, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3,
				     0x01, 0x00, 0x00, 0x00, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf4, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf2, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x50, 0x42);
	mipi_dsi_dcs_set_column_address_multi(&dsi_ctx, 0x0000, 0x0437);
	mipi_dsi_dcs_set_page_address_multi(&dsi_ctx, 0x0000, 0x0923);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);

	return dsi_ctx.accum_err;
}

static int r66451_plus_cphy_144hz_off(struct r66451_plus_cphy_144hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int r66451_plus_cphy_144hz_prepare(struct drm_panel *panel)
{
	struct r66451_plus_cphy_144hz *ctx = to_r66451_plus_cphy_144hz(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	r66451_plus_cphy_144hz_reset(ctx);

	ret = r66451_plus_cphy_144hz_on(ctx);
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

static int r66451_plus_cphy_144hz_unprepare(struct drm_panel *panel)
{
	struct r66451_plus_cphy_144hz *ctx = to_r66451_plus_cphy_144hz(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = r66451_plus_cphy_144hz_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode r66451_plus_cphy_144hz_mode = {
	.clock = (1080 + 96 + 32 + 40) * (2340 + 25 + 1 + 4) * 144 / 1000,
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

static int r66451_plus_cphy_144hz_get_modes(struct drm_panel *panel,
					    struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &r66451_plus_cphy_144hz_mode);
}

static const struct drm_panel_funcs r66451_plus_cphy_144hz_panel_funcs = {
	.prepare = r66451_plus_cphy_144hz_prepare,
	.unprepare = r66451_plus_cphy_144hz_unprepare,
	.get_modes = r66451_plus_cphy_144hz_get_modes,
};

static int r66451_plus_cphy_144hz_bl_update_status(struct backlight_device *bl)
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
static int r66451_plus_cphy_144hz_bl_get_brightness(struct backlight_device *bl)
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

static const struct backlight_ops r66451_plus_cphy_144hz_bl_ops = {
	.update_status = r66451_plus_cphy_144hz_bl_update_status,
	.get_brightness = r66451_plus_cphy_144hz_bl_get_brightness,
};

static struct backlight_device *
r66451_plus_cphy_144hz_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 4095,
		.max_brightness = 4095,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &r66451_plus_cphy_144hz_bl_ops, &props);
}

static int r66451_plus_cphy_144hz_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct r66451_plus_cphy_144hz *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct r66451_plus_cphy_144hz, panel,
				   &r66451_plus_cphy_144hz_panel_funcs,
				   DRM_MODE_CONNECTOR_DSI);
	if (IS_ERR(ctx))
		return PTR_ERR(ctx);

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 3;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = r66451_plus_cphy_144hz_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 2 */
	ctx->dsc.slice_height = 20;
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

static void r66451_plus_cphy_144hz_remove(struct mipi_dsi_device *dsi)
{
	struct r66451_plus_cphy_144hz *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id r66451_plus_cphy_144hz_of_match[] = {
	{ .compatible = "mdss,r66451-plus-cphy-144hz" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, r66451_plus_cphy_144hz_of_match);

static struct mipi_dsi_driver r66451_plus_cphy_144hz_driver = {
	.probe = r66451_plus_cphy_144hz_probe,
	.remove = r66451_plus_cphy_144hz_remove,
	.driver = {
		.name = "panel-r66451-plus-cphy-144hz",
		.of_match_table = r66451_plus_cphy_144hz_of_match,
	},
};
module_mipi_dsi_driver(r66451_plus_cphy_144hz_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for r66451 amoled video mode dsi visionox panel with DSC");
MODULE_LICENSE("GPL");
