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

struct nt36672c_plus_90hz {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct nt36672c_plus_90hz *to_nt36672c_plus_90hz(struct drm_panel *panel)
{
	return container_of_const(panel, struct nt36672c_plus_90hz, panel);
}

static void nt36672c_plus_90hz_reset(struct nt36672c_plus_90hz *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int nt36672c_plus_90hz_on(struct nt36672c_plus_90hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x1b, 0xa0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x66);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x38);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x66);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5c, 0x90);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS,
				     0xaa);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8e, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8f, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x95, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x96, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf2, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf3, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf4, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf5, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf6, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf7, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf8, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf9, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x1d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x08, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x09, 0x2e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x2d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0b, 0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x12, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x13, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x1d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x2e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x22, 0x2d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x23, 0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2b, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_COLUMNS,
				     0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x32, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x94);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x86, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90, 0x13);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x92, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x93, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x94, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x95, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9c, 0xf4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_PPS_START, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa3, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa4, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa5, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe9, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x1b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0xe4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0xd8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x48);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x41);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x73, 0x4a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x74, 0xd0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x62);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x7f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x0d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xef, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x86, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8c, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8e, 0x42);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9a, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x27);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0xea);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa5, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa6, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa7, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0xe0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe9, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xec, 0x98);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x5a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x4f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0xe4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0xf5);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x54);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0xe6);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x32);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0xe1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0xfe);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x46, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x47, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x52, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x57, 0x7e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x7e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x7e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x60, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0xc9);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x63, 0xfb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x64, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x65, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x66, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x67, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x68, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x19);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0xcb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0xe5);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0xc8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0xe3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x07);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8c, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8d, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8e, 0x39);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x95, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x96, 0xfd);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x97, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x98, 0xb3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x99, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9a, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9c, 0x4c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0xbc);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9f, 0xac);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_PPS_START, 0x44);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa3, 0x78);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa4, 0xf8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa5, 0x4a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa6, 0x72);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa7, 0x4c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x02, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x04, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x05, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0e, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0x1b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x17, 0x4b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x18, 0x4b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x4b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x2f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x56, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x58, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x59, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x61, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x62, 0x1f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6a, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6b, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6c, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6d, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0x0e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9e, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xe0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x00, 0x00, 0x15, 0x00, 0x3f, 0x00,
				     0x5f, 0x00, 0x7e, 0x00, 0x97, 0x00, 0xaf,
				     0x00, 0xc3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x00, 0xd7, 0x01, 0x0a, 0x01, 0x32, 0x01,
				     0x6f, 0x01, 0x9e, 0x01, 0xe5, 0x02, 0x1d,
				     0x02, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x56, 0x02, 0x94, 0x02, 0xbc, 0x02,
				     0xf1, 0x03, 0x13, 0x03, 0x41, 0x03, 0x4f,
				     0x03, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x71, 0x03, 0x84, 0x03, 0x99, 0x03,
				     0xb0, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x00, 0x00, 0x17, 0x00, 0x46, 0x00,
				     0x69, 0x00, 0x8c, 0x00, 0xa5, 0x00, 0xbe,
				     0x00, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0xe4, 0x01, 0x18, 0x01, 0x40, 0x01,
				     0x7c, 0x01, 0xaa, 0x01, 0xf0, 0x02, 0x27,
				     0x02, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x5e, 0x02, 0x9b, 0x02, 0xc3, 0x02,
				     0xf6, 0x03, 0x18, 0x03, 0x45, 0x03, 0x54,
				     0x03, 0x63);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x75, 0x03, 0x87, 0x03, 0x9c, 0x03,
				     0xb2, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x00, 0x00, 0x18, 0x00, 0x49, 0x00,
				     0x6b, 0x00, 0x8e, 0x00, 0xa8, 0x00, 0xc1,
				     0x00, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0xe5, 0x01, 0x18, 0x01, 0x3f, 0x01,
				     0x7b, 0x01, 0xa8, 0x01, 0xec, 0x02, 0x24,
				     0x02, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x5a, 0x02, 0x97, 0x02, 0xc0, 0x02,
				     0xf4, 0x03, 0x15, 0x03, 0x43, 0x03, 0x51,
				     0x03, 0x61);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x72, 0x03, 0x85, 0x03, 0x9a, 0x03,
				     0xb1, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcb, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcc, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcd, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xce, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd4, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd5, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xda, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdb, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdc, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdd, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xde, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xdf, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe1, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe2, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe3, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe4, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe7, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe9, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x00, 0x00, 0x15, 0x00, 0x3f, 0x00,
				     0x5f, 0x00, 0x7e, 0x00, 0x97, 0x00, 0xaf,
				     0x00, 0xc3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x00, 0xd7, 0x01, 0x0a, 0x01, 0x32, 0x01,
				     0x6f, 0x01, 0x9e, 0x01, 0xe5, 0x02, 0x1d,
				     0x02, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x56, 0x02, 0x94, 0x02, 0xbc, 0x02,
				     0xf1, 0x03, 0x13, 0x03, 0x41, 0x03, 0x4f,
				     0x03, 0x5f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x71, 0x03, 0x84, 0x03, 0x99, 0x03,
				     0xb0, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x00, 0x00, 0x17, 0x00, 0x46, 0x00,
				     0x69, 0x00, 0x8c, 0x00, 0xa5, 0x00, 0xbe,
				     0x00, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0xe4, 0x01, 0x18, 0x01, 0x40, 0x01,
				     0x7c, 0x01, 0xaa, 0x01, 0xf0, 0x02, 0x27,
				     0x02, 0x28);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x5e, 0x02, 0x9b, 0x02, 0xc3, 0x02,
				     0xf6, 0x03, 0x18, 0x03, 0x45, 0x03, 0x54,
				     0x03, 0x63);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x75, 0x03, 0x87, 0x03, 0x9c, 0x03,
				     0xb2, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x00, 0x00, 0x18, 0x00, 0x49, 0x00,
				     0x6b, 0x00, 0x8e, 0x00, 0xa8, 0x00, 0xc1,
				     0x00, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0xe5, 0x01, 0x18, 0x01, 0x3f, 0x01,
				     0x7b, 0x01, 0xa8, 0x01, 0xec, 0x02, 0x24,
				     0x02, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x5a, 0x02, 0x97, 0x02, 0xc0, 0x02,
				     0xf4, 0x03, 0x15, 0x03, 0x43, 0x03, 0x51,
				     0x03, 0x61);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x72, 0x03, 0x85, 0x03, 0x9a, 0x03,
				     0xb1, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1c, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x52);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xd0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x54, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xc0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9c, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x2b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_set_tear_on_multi(&dsi_ctx, MIPI_DSI_DCS_TEAR_MODE_VHBLANK);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x00ff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x0c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 200);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);

	return dsi_ctx.accum_err;
}

static int nt36672c_plus_90hz_off(struct nt36672c_plus_90hz *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_usleep_range(&dsi_ctx, 16000, 17000);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);

	return dsi_ctx.accum_err;
}

static int nt36672c_plus_90hz_prepare(struct drm_panel *panel)
{
	struct nt36672c_plus_90hz *ctx = to_nt36672c_plus_90hz(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	nt36672c_plus_90hz_reset(ctx);

	ret = nt36672c_plus_90hz_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int nt36672c_plus_90hz_unprepare(struct drm_panel *panel)
{
	struct nt36672c_plus_90hz *ctx = to_nt36672c_plus_90hz(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = nt36672c_plus_90hz_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

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

static int nt36672c_plus_90hz_get_modes(struct drm_panel *panel,
					struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &nt36672c_plus_90hz_mode);
}

static const struct drm_panel_funcs nt36672c_plus_90hz_panel_funcs = {
	.prepare = nt36672c_plus_90hz_prepare,
	.unprepare = nt36672c_plus_90hz_unprepare,
	.get_modes = nt36672c_plus_90hz_get_modes,
};

static int nt36672c_plus_90hz_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt36672c_plus_90hz *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct nt36672c_plus_90hz, panel,
				   &nt36672c_plus_90hz_panel_funcs,
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

static void nt36672c_plus_90hz_remove(struct mipi_dsi_device *dsi)
{
	struct nt36672c_plus_90hz *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id nt36672c_plus_90hz_of_match[] = {
	{ .compatible = "mdss,nt36672c-plus-90hz" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt36672c_plus_90hz_of_match);

static struct mipi_dsi_driver nt36672c_plus_90hz_driver = {
	.probe = nt36672c_plus_90hz_probe,
	.remove = nt36672c_plus_90hz_remove,
	.driver = {
		.name = "panel-nt36672c-plus-90hz",
		.of_match_table = nt36672c_plus_90hz_of_match,
	},
};
module_mipi_dsi_driver(nt36672c_plus_90hz_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for nt36672c fhd plus 90Hz CPHY video panel");
MODULE_LICENSE("GPL");
