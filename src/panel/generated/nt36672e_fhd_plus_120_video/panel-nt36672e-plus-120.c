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

struct nt36672e_plus_120 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct drm_dsc_config dsc;
	struct gpio_desc *reset_gpio;
};

static inline
struct nt36672e_plus_120 *to_nt36672e_plus_120(struct drm_panel *panel)
{
	return container_of_const(panel, struct nt36672e_plus_120, panel);
}

static void nt36672e_plus_120_reset(struct nt36672e_plus_120 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int nt36672e_plus_120_on(struct nt36672e_plus_120 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1,
				     0x89, 0x28, 0x00, 0x08, 0x00, 0xaa, 0x02,
				     0x0e, 0x00, 0x2b, 0x00, 0x07, 0x0d, 0xb7,
				     0x0c, 0xb7);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x1b, 0xa0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x66);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x06, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x38);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2f, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x69, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x95, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x96, 0xd1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf2, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf4, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf6, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf8, 0x64);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x1c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8c, 0x1c);
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
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4d, 0x14);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4e, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4f, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7a, 0x82);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7b, 0x8f);
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
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa0, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_READ_PPS_START, 0x0f);
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
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x79, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x4d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xef, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0, 0x84);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x26);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x81, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x84, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x85, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x86, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x87, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8a, 0x1a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8b, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8c, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8e, 0x42);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x8f, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x90, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x91, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9a, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9b, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9c, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9d, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x9e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x27);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x01, 0x68);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x21, 0x6a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x25, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_GAMMA_CURVE, 0x94);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6e, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x70, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x71, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x72, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x75, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x76, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x77, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7d, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x7e, 0x67);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x80, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x82, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x83, 0x67);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x88, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x89, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa5, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa6, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xa7, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x2a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x00, 0x91);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x03, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x07, 0x50);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0a, 0x70);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0c, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0d, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x0f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x11, 0xe0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x15, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x16, 0xa4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x19, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1a, 0x78);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1b, 0x23);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1d, 0x36);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1e, 0x3e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x1f, 0x3e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x20, 0x3e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x28, 0xfd);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x29, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x2a, 0xe1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_LUT, 0x0a);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_PARTIAL_ROWS, 0x49);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x33, 0x96);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x34, 0xff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x35, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_SET_ADDRESS_MODE, 0xde);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x37, 0xf9);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x38, 0x45);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x39, 0xd9);
	mipi_dsi_dcs_set_pixel_format_multi(&dsi_ctx, 0x49);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x4a, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x00, 0x00, 0x17, 0x00, 0x46, 0x00,
				     0x63, 0x00, 0x81, 0x00, 0x96, 0x00, 0xab,
				     0x00, 0xbd);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x00, 0xcf, 0x01, 0x03, 0x01, 0x2f, 0x01,
				     0x6e, 0x01, 0x9d, 0x01, 0xe7, 0x02, 0x22,
				     0x02, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x5d, 0x02, 0x9b, 0x02, 0xc4, 0x02,
				     0xf9, 0x03, 0x1b, 0x03, 0x48, 0x03, 0x56,
				     0x03, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x75, 0x03, 0x87, 0x03, 0x9b, 0x03,
				     0xb1, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x00, 0x00, 0x19, 0x00, 0x4b, 0x00,
				     0x69, 0x00, 0x87, 0x00, 0x9c, 0x00, 0xb2,
				     0x00, 0xc3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0xd5, 0x01, 0x0b, 0x01, 0x35, 0x01,
				     0x73, 0x01, 0xa3, 0x01, 0xec, 0x02, 0x27,
				     0x02, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x60, 0x02, 0x9f, 0x02, 0xc7, 0x02,
				     0xfb, 0x03, 0x1d, 0x03, 0x4c, 0x03, 0x5a,
				     0x03, 0x69);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x7a, 0x03, 0x8c, 0x03, 0xa0, 0x03,
				     0xb5, 0x03, 0xcb, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x00, 0x00, 0x19, 0x00, 0x4d, 0x00,
				     0x6a, 0x00, 0x87, 0x00, 0x9c, 0x00, 0xb1,
				     0x00, 0xc2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0xd3, 0x01, 0x08, 0x01, 0x32, 0x01,
				     0x70, 0x01, 0x9f, 0x01, 0xe8, 0x02, 0x23,
				     0x02, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x5c, 0x02, 0x9b, 0x02, 0xc3, 0x02,
				     0xf8, 0x03, 0x1a, 0x03, 0x4c, 0x03, 0x5b,
				     0x03, 0x6b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x7d, 0x03, 0x92, 0x03, 0xa7, 0x03,
				     0xbb, 0x03, 0xce, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x21);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x00, 0x00, 0x17, 0x00, 0x46, 0x00,
				     0x63, 0x00, 0x81, 0x00, 0x96, 0x00, 0xab,
				     0x00, 0xbd);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x00, 0xcf, 0x01, 0x03, 0x01, 0x2f, 0x01,
				     0x6e, 0x01, 0x9d, 0x01, 0xe7, 0x02, 0x22,
				     0x02, 0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0x5d, 0x02, 0x9b, 0x02, 0xc4, 0x02,
				     0xf9, 0x03, 0x1b, 0x03, 0x48, 0x03, 0x56,
				     0x03, 0x65);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x03, 0x75, 0x03, 0x87, 0x03, 0x9b, 0x03,
				     0xb1, 0x03, 0xca, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x00, 0x00, 0x19, 0x00, 0x4b, 0x00,
				     0x69, 0x00, 0x87, 0x00, 0x9c, 0x00, 0xb2,
				     0x00, 0xc3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x00, 0xd5, 0x01, 0x0b, 0x01, 0x35, 0x01,
				     0x73, 0x01, 0xa3, 0x01, 0xec, 0x02, 0x27,
				     0x02, 0x29);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0x60, 0x02, 0x9f, 0x02, 0xc7, 0x02,
				     0xfb, 0x03, 0x1d, 0x03, 0x4c, 0x03, 0x5a,
				     0x03, 0x69);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x03, 0x7a, 0x03, 0x8c, 0x03, 0xa0, 0x03,
				     0xb5, 0x03, 0xcb, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x00, 0x00, 0x19, 0x00, 0x4d, 0x00,
				     0x6a, 0x00, 0x87, 0x00, 0x9c, 0x00, 0xb1,
				     0x00, 0xc2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x00, 0xd3, 0x01, 0x08, 0x01, 0x32, 0x01,
				     0x70, 0x01, 0x9f, 0x01, 0xe8, 0x02, 0x23,
				     0x02, 0x25);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0x5c, 0x02, 0x9b, 0x02, 0xc3, 0x02,
				     0xf8, 0x03, 0x1a, 0x03, 0x4c, 0x03, 0x5b,
				     0x03, 0x6b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x03, 0x7d, 0x03, 0x92, 0x03, 0xa7, 0x03,
				     0xbb, 0x03, 0xce, 0x03, 0xd7, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xf0);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x5a, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xfb, 0x01);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x00ff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x2c);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x01);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 200);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 150);

	return dsi_ctx.accum_err;
}

static int nt36672e_plus_120_off(struct nt36672e_plus_120 *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_usleep_range(&dsi_ctx, 16000, 17000);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);

	return dsi_ctx.accum_err;
}

static int nt36672e_plus_120_prepare(struct drm_panel *panel)
{
	struct nt36672e_plus_120 *ctx = to_nt36672e_plus_120(panel);
	struct device *dev = &ctx->dsi->dev;
	struct drm_dsc_picture_parameter_set pps;
	int ret;

	nt36672e_plus_120_reset(ctx);

	ret = nt36672e_plus_120_on(ctx);
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

static int nt36672e_plus_120_unprepare(struct drm_panel *panel)
{
	struct nt36672e_plus_120 *ctx = to_nt36672e_plus_120(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = nt36672e_plus_120_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode nt36672e_plus_120_mode = {
	.clock = (1080 + 80 + 12 + 60) * (2408 + 46 + 10 + 10) * 120 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 80,
	.hsync_end = 1080 + 80 + 12,
	.htotal = 1080 + 80 + 12 + 60,
	.vdisplay = 2408,
	.vsync_start = 2408 + 46,
	.vsync_end = 2408 + 46 + 10,
	.vtotal = 2408 + 46 + 10 + 10,
	.width_mm = 0,
	.height_mm = 0,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int nt36672e_plus_120_get_modes(struct drm_panel *panel,
				       struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &nt36672e_plus_120_mode);
}

static const struct drm_panel_funcs nt36672e_plus_120_panel_funcs = {
	.prepare = nt36672e_plus_120_prepare,
	.unprepare = nt36672e_plus_120_unprepare,
	.get_modes = nt36672e_plus_120_get_modes,
};

static int nt36672e_plus_120_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct nt36672e_plus_120 *ctx;
	int ret;

	ctx = devm_drm_panel_alloc(dev, struct nt36672e_plus_120, panel,
				   &nt36672e_plus_120_panel_funcs,
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

	/* This panel only supports DSC; unconditionally enable it */
	dsi->dsc = &ctx->dsc;

	ctx->dsc.dsc_version_major = 1;
	ctx->dsc.dsc_version_minor = 1;

	/* TODO: Pass slice_per_pkt = 1 */
	ctx->dsc.slice_height = 8;
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

static void nt36672e_plus_120_remove(struct mipi_dsi_device *dsi)
{
	struct nt36672e_plus_120 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id nt36672e_plus_120_of_match[] = {
	{ .compatible = "mdss,nt36672e-plus-120" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, nt36672e_plus_120_of_match);

static struct mipi_dsi_driver nt36672e_plus_120_driver = {
	.probe = nt36672e_plus_120_probe,
	.remove = nt36672e_plus_120_remove,
	.driver = {
		.name = "panel-nt36672e-plus-120",
		.of_match_table = nt36672e_plus_120_of_match,
	},
};
module_mipi_dsi_driver(nt36672e_plus_120_driver);

MODULE_AUTHOR("linux-mdss-dsi-panel-driver-generator <fix@me>"); // FIXME
MODULE_DESCRIPTION("DRM driver for nt36672e lcd video mode dsi novatek panel with DSC");
MODULE_LICENSE("GPL");
