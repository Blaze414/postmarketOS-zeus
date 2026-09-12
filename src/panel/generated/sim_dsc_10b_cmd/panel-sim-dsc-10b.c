// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2026 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/backlight.h>
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

struct sim_dsc_10b {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline struct sim_dsc_10b *to_sim_dsc_10b(struct drm_panel *panel)
{
	return container_of_const(panel, struct sim_dsc_10b, panel);
}

static void sim_dsc_10b_reset(struct sim_dsc_10b *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int sim_dsc_10b_on(struct sim_dsc_10b *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x55);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0xb0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0xae);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0xb8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5d, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x10, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x14, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x89);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x8a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x24, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x6d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x27, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdc, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdd, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3, 0x6d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2, 0x07);
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
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5b, 0x43);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5f, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x73);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7c, 0xd8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x78, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x93, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x94, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0xb0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9f, 0x63);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x98, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xec, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
				     0x09, 0x20, 0x00, 0x10, 0x02, 0x00, 0x02,
				     0x68, 0x01, 0xbb, 0x00, 0x0a, 0x06, 0x67,
				     0x04, 0xc5);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x10, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x3b, 0x03);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_nop_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 240);

	return dsi_ctx.accum_err;
}

static int sim_dsc_10b_off(struct sim_dsc_10b *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int sim_dsc_10b_prepare(struct drm_panel *panel)
{
	struct sim_dsc_10b *ctx = to_sim_dsc_10b(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	sim_dsc_10b_reset(ctx);

	ret = sim_dsc_10b_on(ctx);
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

static int sim_dsc_10b_unprepare(struct drm_panel *panel)
{
	struct sim_dsc_10b *ctx = to_sim_dsc_10b(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = sim_dsc_10b_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode sim_dsc_10b_mode = {
	.clock = (1440 + 100 + 16 + 32) * (2560 + 10 + 2 + 8) * 60 / 1000,
	.hdisplay = 1440,
	.hsync_start = 1440 + 100,
	.hsync_end = 1440 + 100 + 16,
	.htotal = 1440 + 100 + 16 + 32,
	.vdisplay = 2560,
	.vsync_start = 2560 + 10,
	.vsync_end = 2560 + 10 + 2,
	.vtotal = 2560 + 10 + 2 + 8,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int sim_dsc_10b_get_modes(struct drm_panel *panel,
				 struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &sim_dsc_10b_mode);
}

static const struct drm_panel_funcs sim_dsc_10b_panel_funcs = {
	.prepare = sim_dsc_10b_prepare,
	.unprepare = sim_dsc_10b_unprepare,
	.get_modes = sim_dsc_10b_get_modes,
};

static int sim_dsc_10b_bl_update_status(struct backlight_device *bl)
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
static int sim_dsc_10b_bl_get_brightness(struct backlight_device *bl)
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

static const struct backlight_ops sim_dsc_10b_bl_ops = {
	.update_status = sim_dsc_10b_bl_update_status,
	.get_brightness = sim_dsc_10b_bl_get_brightness,
};

static struct backlight_device *
sim_dsc_10b_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 4095,
		.max_brightness = 4095,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &sim_dsc_10b_bl_ops, &props);
}

static int sim_dsc_10b_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct sim_dsc_10b *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct sim_dsc_10b, panel,
				   &sim_dsc_10b_panel_funcs,
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
	dsi->mode_flags = MIPI_DSI_MODE_NO_EOT_PACKET |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS;

	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = sim_dsc_10b_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 2 */
	ctx->dsc.slice_height = 16;
	ctx->dsc.slice_width = 720;
	/*
	 * TODO: hdisplay should be read from the selected mode once
	 * it is passed back to drm_panel (in prepare?)
	 */
	WARN_ON(1440 % ctx->dsc.slice_width);
	ctx->dsc.slice_count = 1440 / ctx->dsc.slice_width;
	ctx->dsc.bits_per_component = 10;
	ctx->dsc.bits_per_pixel = 10 << 4; /* 4 fractional bits */
	ctx->dsc.block_pred_enable = true;

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void sim_dsc_10b_remove(struct mipi_dsi_device *dsi)
{
	struct sim_dsc_10b *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id sim_dsc_10b_of_match[] = {
	{ .compatible = "sim,dsc-10b" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, sim_dsc_10b_of_match);

static struct mipi_dsi_driver sim_dsc_10b_driver = {
	.probe = sim_dsc_10b_probe,
	.remove = sim_dsc_10b_remove,
	.driver = {
		.name = "panel-sim-dsc-10b",
		.of_match_table = sim_dsc_10b_of_match,
	},
};
module_mipi_dsi_driver(sim_dsc_10b_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for Simulator cmd mode DSC3:1 10bit dsi panel");
MODULE_LICENSE("GPL");
