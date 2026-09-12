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

struct r66451_plus_90hz_cphy_nodsc {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct r66451_plus_90hz_cphy_nodsc *to_r66451_plus_90hz_cphy_nodsc(struct drm_panel *panel)
{
	return container_of_const(panel, struct r66451_plus_90hz_cphy_nodsc, panel);
}

static void r66451_plus_90hz_cphy_nodsc_reset(struct r66451_plus_90hz_cphy_nodsc *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int r66451_plus_90hz_cphy_nodsc_on(struct r66451_plus_90hz_cphy_nodsc *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x6c, 0x00, 0x06, 0x23, 0x92);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2,
				     0x09, 0x24, 0x0c, 0x00, 0x00, 0x0c, 0x00,
				     0x00, 0x00, 0x09, 0x3c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7,
				     0x00, 0xb9, 0x3c, 0x00, 0x40, 0x04, 0x00,
				     0xa0, 0x0a, 0x00, 0x40, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x19, 0x3c, 0x00, 0x40,
				     0x04, 0x00, 0xa0, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde,
				     0x40, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18,
				     0x00, 0x18, 0x10, 0x00, 0x18, 0x00, 0x18,
				     0x00, 0x18, 0x02, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x00, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
				     0x00, 0x32);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf,
				     0x64, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x08, 0x00, 0x0b, 0x77, 0x01, 0x01,
				     0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02,
				     0x02, 0x02, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3,
				     0x45, 0x00, 0x00, 0x01, 0x13, 0x15, 0x00,
				     0x15, 0x07, 0x0f, 0x77, 0x77, 0x77, 0x37,
				     0xb2, 0x11, 0x00, 0xa0, 0x3c, 0x9c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7,
				     0x00, 0xb9, 0x34, 0x00, 0x40, 0x04, 0x00,
				     0xa0, 0x0a, 0x00, 0x40, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x19, 0x34, 0x00, 0x40,
				     0x04, 0x00, 0xa0, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x3a, 0x00, 0x3a, 0x00, 0x3a,
				     0x00, 0x3a, 0x00, 0x3a, 0x05, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x0a, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x0a, 0x00, 0x32, 0x00, 0x0a,
				     0x00, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf,
				     0x50, 0x42, 0x58, 0x81, 0x2d, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x6b, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
				     0x0f, 0xff, 0xd4, 0x0e, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x0f, 0x53, 0xf1, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf7, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4,
				     0x34, 0xb4, 0x00, 0x00, 0x00, 0x39, 0x04,
				     0x09, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf7, 0x00);
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
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2,
				     0x09, 0x24, 0x0c, 0x00, 0x00, 0x0c, 0x03,
				     0x14, 0x00, 0x09, 0x3c, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x30, 0x00, 0x6c);

	return dsi_ctx.accum_err;
}

static int r66451_plus_90hz_cphy_nodsc_off(struct r66451_plus_90hz_cphy_nodsc *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int r66451_plus_90hz_cphy_nodsc_prepare(struct drm_panel *panel)
{
	struct r66451_plus_90hz_cphy_nodsc *ctx = to_r66451_plus_90hz_cphy_nodsc(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	r66451_plus_90hz_cphy_nodsc_reset(ctx);

	ret = r66451_plus_90hz_cphy_nodsc_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int r66451_plus_90hz_cphy_nodsc_unprepare(struct drm_panel *panel)
{
	struct r66451_plus_90hz_cphy_nodsc *ctx = to_r66451_plus_90hz_cphy_nodsc(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = r66451_plus_90hz_cphy_nodsc_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

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

static int r66451_plus_90hz_cphy_nodsc_get_modes(struct drm_panel *panel,
						 struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &r66451_plus_90hz_cphy_nodsc_mode);
}

static const struct drm_panel_funcs r66451_plus_90hz_cphy_nodsc_panel_funcs = {
	.prepare = r66451_plus_90hz_cphy_nodsc_prepare,
	.unprepare = r66451_plus_90hz_cphy_nodsc_unprepare,
	.get_modes = r66451_plus_90hz_cphy_nodsc_get_modes,
};

static int r66451_plus_90hz_cphy_nodsc_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct r66451_plus_90hz_cphy_nodsc *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct r66451_plus_90hz_cphy_nodsc, panel,
				   &r66451_plus_90hz_cphy_nodsc_panel_funcs,
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

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void r66451_plus_90hz_cphy_nodsc_remove(struct mipi_dsi_device *dsi)
{
	struct r66451_plus_90hz_cphy_nodsc *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id r66451_plus_90hz_cphy_nodsc_of_match[] = {
	{ .compatible = "mdss,r66451-plus-90hz-cphy-nodsc" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, r66451_plus_90hz_cphy_nodsc_of_match);

static struct mipi_dsi_driver r66451_plus_90hz_cphy_nodsc_driver = {
	.probe = r66451_plus_90hz_cphy_nodsc_probe,
	.remove = r66451_plus_90hz_cphy_nodsc_remove,
	.driver = {
		.name = "panel-r66451-plus-90hz-cphy-nodsc",
		.of_match_table = r66451_plus_90hz_cphy_nodsc_of_match,
	},
};
module_mipi_dsi_driver(r66451_plus_90hz_cphy_nodsc_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for r66451 amoled video mode dsi visionox panel without DSC");
MODULE_LICENSE("GPL");
