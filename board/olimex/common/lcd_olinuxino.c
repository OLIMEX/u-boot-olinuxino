/*
 * Copyright (C) 2018 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */
#include <common.h>
#include <dm.h>
#include <env.h>
#include <i2c.h>
#include <u-boot/crc.h>

#include <olimex/lcd_olinuxino.h>

struct lcd_olinuxino_board lcd_olinuxino_boards[] = {
	{
		.id = 7859,
		.compatible = "olimex,lcd-olinuxino-4.3",
		{
			.name = "LCD-OLinuXino-4.3TS",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 12000,
			.hactive = 480,
			.hfp = 8,
			.hbp = 23,
			.hpw = 20,
			.vactive = 272,
			.vfp = 4,
			.vbp = 13,
			.vpw = 10,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 8630,
		.compatible = "olimex,lcd-olinuxino-5",
		{
			.name = "LCD-OLinuXino-5",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 33000,
			.hactive = 800,
			.hfp = 210,
			.hbp = 26,
			.hpw = 20,
			.vactive = 480,
			.vfp = 22,
			.vbp = 13,
			.vpw = 10,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 7864,
		.compatible = "olimex,lcd-olinuxino-7",
		{
			.name = "LCD-OLinuXino-7",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 33000,
			.hactive = 800,
			.hfp = 210,
			.hbp = 26,
			.hpw = 20,
			.vactive = 480,
			.vfp = 22,
			.vbp = 13,
			.vpw = 10,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 9278,
		.compatible = "olimex,lcd-olinuxino-10",
		{
			.name = "LCD-OLinuXino-7CTS",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 45000,
			.hactive = 1024,
			.hfp = 15,
			.hbp = 160,
			.hpw = 1,
			.vactive = 600,
			.vfp = 1,
			.vbp = 22,
			.vpw = 1,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 7862,
		.compatible = "olimex,lcd-olinuxino-10",
		{
			.name = "LCD-OLinuXino-10",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 45000,
			.hactive = 1024,
			.hfp = 15,
			.hbp = 160,
			.hpw = 1,
			.vactive = 600,
			.vfp = 1,
			.vbp = 22,
			.vpw = 1,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 9284,
		.compatible = "olimex,lcd-olinuxino-10",
		{
			.name = "LCD-OLinuXino-10CTS",
			.bus_format = MEDIA_BUS_FMT_RGB888_1X24,
		},
		{
			.pixelclock = 45000,
			.hactive = 1024,
			.hfp = 15,
			.hbp = 160,
			.hpw = 1,
			.vactive = 600,
			.vfp = 1,
			.vbp = 22,
			.vpw = 1,
			.refresh = 60,
			.flags = 0
		}

	},
#ifdef CONFIG_TARGET_A20_OLINUXINO
	{
		.id = 7891,
		.compatible = "",
		{
			.name = "LCD-OLinuXino-15.6",
		},
		{
			.pixelclock = 70000,
			.hactive = 1366,
			.hfp = 20,
			.hbp = 54,
			.hpw = 0,
			.vactive = 768,
			.vfp = 17,
			.vbp = 23,
			.vpw = 0,
			.refresh = 60,
			.flags = 0
		}

	},
	{
		.id = 7894,
		.compatible = "",
		{
			.name = "LCD-OLinuXino-15.6FHD",
		},
		{
			.pixelclock = 152000,
			.hactive = 1920,
			.hfp = 150,
			.hbp = 246,
			.hpw = 60,
			.vactive = 1080,
			.vfp = 15,
			.vbp = 53,
			.vpw = 9,
			.refresh = 60,
			.flags = 0
		}

	},
#endif
	{
		.id = 0,
	},
};

struct lcd_olinuxino_eeprom lcd_olinuxino_eeprom;


static int lcd_olinuxino_eeprom_read(void)
{
	uint32_t crc;
	int ret;

#ifdef CONFIG_DM_I2C
	struct udevice *bus, *chip;

	ret = uclass_get_device_by_seq(UCLASS_I2C, LCD_OLINUXINO_EEPROM_BUS, &bus);
	if (ret)
		return ret;

	ret = dm_i2c_probe(bus, 0x50, 0x0, &chip);
	if (ret)
		return ret;

	ret = dm_i2c_read(chip, 0x00, (uint8_t *)&lcd_olinuxino_eeprom, 256);
	if (ret)
		return ret;
#else
	ret = i2c_set_bus_num(LCD_OLINUXINO_EEPROM_BUS);
	if (ret)
		return ret;

	ret = i2c_probe(LCD_OLINUXINO_EEPROM_ADDRESS);
	if (ret)
		return ret;

	ret = i2c_read(LCD_OLINUXINO_EEPROM_ADDRESS, 0, 1, (uint8_t *)&lcd_olinuxino_eeprom, 256);
	if (ret)
		return ret;
#endif

	if (lcd_olinuxino_eeprom.header != LCD_OLINUXINO_HEADER_MAGIC)
		goto error;

	crc = crc32(0L, (uint8_t *)&lcd_olinuxino_eeprom, 252);
	if (lcd_olinuxino_eeprom.checksum != crc)
		goto error;

	return 0;

error:
	memset(&lcd_olinuxino_eeprom, 0xFF, 256);
	return -ENODEV;
}

#ifdef CONFIG_VIDEO_SUNXI
char videomode[128];

char * lcd_olinuxino_video_mode()
{
	struct lcd_olinuxino_mode *mode = NULL;
	struct lcd_olinuxino_info *info = NULL;
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);
	uint32_t i;
	int ret;


	if (id) {
		for (i = 0; i < ARRAY_SIZE(lcd_olinuxino_boards); i++) {
			if (lcd_olinuxino_boards[i].id == id) {
				info = &lcd_olinuxino_boards[i].info;
				mode = &lcd_olinuxino_boards[i].mode;
				break;
			}
		}
	}

	if (mode == NULL || info == NULL) {
		ret = lcd_olinuxino_eeprom_read();
		if (ret)
			return "";

		printf("\nDetected %s, Rev.%s, Serial:%08x\n",
		       lcd_olinuxino_eeprom.info.name,
		       lcd_olinuxino_eeprom.revision,
		       lcd_olinuxino_eeprom.serial);

		mode = (struct lcd_olinuxino_mode *)&lcd_olinuxino_eeprom.reserved;
		info = &lcd_olinuxino_eeprom.info;
	}

	/**
	 * If LCD is explicitly selected or auto-detected, make monitor=lcd as
	 * default. This way the HDMI will not take over the console.
	 */
	env_set("video-mode", "sunxi:1024x768-24@60,monitor=lcd");
	sprintf(videomode, "x:%d,y:%d,depth:%d,pclk_khz:%d,le:%d,ri:%d,up:%d,lo:%d,hs:%d,vs:%d,sync:3,vmode:0",
		mode->hactive,
		mode->vactive,
		(info->bus_format == MEDIA_BUS_FMT_RGB888_1X24) ? 24 : 18,
		mode->pixelclock,
		mode->hbp,
		mode->hfp,
		mode->vbp,
		mode->vfp,
		mode->hpw,
		mode->vpw);


	return videomode;
}
#endif /* CONFIG_VIDEO_SUNXI */

#ifdef CONFIG_VIDEO_DE2
int lcd_olinuxino_display_timing(struct display_timing *timing)
{
	struct lcd_olinuxino_mode *mode = NULL;
	struct lcd_olinuxino_info *info = NULL;
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);
	uint32_t i;
	int ret;

	if (id) {
		for (i = 0; i < ARRAY_SIZE(lcd_olinuxino_boards); i++) {
			if (lcd_olinuxino_boards[i].id == id) {
				info = &lcd_olinuxino_boards[i].info;
				mode = &lcd_olinuxino_boards[i].mode;
				break;
			}
		}
	}

	if (mode == NULL || info == NULL) {
		ret = lcd_olinuxino_eeprom_read();
		if (ret)
			return -ENODEV;

		printf("Detected %s, Rev.%s, Serial:%08x\n",
		       lcd_olinuxino_eeprom.info.name,
		       lcd_olinuxino_eeprom.revision,
		       lcd_olinuxino_eeprom.serial);

		mode = (struct lcd_olinuxino_mode *)&lcd_olinuxino_eeprom.reserved;
		info = &lcd_olinuxino_eeprom.info;
	}

	memset(timing, 0, sizeof(*timing));

	timing->pixelclock.typ = mode->pixelclock * 1000;
	timing->pixelclock.min = timing->pixelclock.typ;
	timing->pixelclock.max = timing->pixelclock.typ;

	timing->hactive.typ = mode->hactive;
	timing->hactive.min = timing->hactive.typ;
	timing->hactive.max = timing->hactive.typ;

	timing->hfront_porch.typ = mode->hfp;
	timing->hfront_porch.min = timing->hfront_porch.typ;
	timing->hfront_porch.max = timing->hfront_porch.typ;

	timing->hback_porch.typ = mode->hbp;
	timing->hback_porch.min = timing->hback_porch.typ;
	timing->hback_porch.max = timing->hback_porch.typ;

	timing->hsync_len.typ = mode->hpw;
	timing->hsync_len.min = timing->hsync_len.typ;
	timing->hsync_len.max = timing->hsync_len.typ;

	timing->vactive.typ = mode->vactive;
	timing->vactive.min = timing->vactive.typ;
	timing->vactive.max = timing->vactive.typ;

	timing->vfront_porch.typ = mode->vfp;
	timing->vfront_porch.min = timing->vfront_porch.typ;
	timing->vfront_porch.max = timing->vfront_porch.typ;

	timing->vback_porch.typ = mode->vbp;
	timing->vback_porch.min = timing->vback_porch.typ;
	timing->vback_porch.max = timing->vback_porch.typ;

	timing->vsync_len.typ = mode->vpw;
	timing->vsync_len.min = timing->vsync_len.typ;
	timing->vsync_len.max = timing->vsync_len.typ;

	timing->flags = mode->flags;
	timing->hdmi_monitor = false;

	return 0;
}
#endif



/**
 * lcd_olinuxino_is_present() - Check if display panel is present
 *
 * If lcd_olinuxino env variable is passed, then always assume present,
 * otherwise check the eeprom for magic header.
 *
 * @return true of present, false - not present
 */
bool lcd_olinuxino_is_present(void)
{
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);

	if (!id)
		return (lcd_olinuxino_eeprom.header == LCD_OLINUXINO_HEADER_MAGIC);
	else
		return true;
}

/**
 * lcd_olinuxino_interface() - Get LCD interface
 *
 * Check if connected LCD interface is either
 *
 * @return interface number
 */
uint8_t lcd_olinuxino_interface(void)
{
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);

	/* Check LVDS or PARALLEL */
	return (id == 7891 || id == 7894) ?
		LCD_OLINUXINO_IF_LVDS :
		LCD_OLINUXINO_IF_PARALLEL;
}

/**
 * lcd_olinuxino_get_data() - Get data for static described LCD
 *
 * @return lcd data structure or NULL
 */
struct lcd_olinuxino_board * lcd_olinuxino_get_data()
{
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);
	uint32_t i;

	if (!id)
		return NULL;

	for (i = 0; i < ARRAY_SIZE(lcd_olinuxino_boards); i++) {
		if (lcd_olinuxino_boards[i].id == id)
			return &lcd_olinuxino_boards[i];
	}

	return NULL;
}

uint32_t lcd_olinuxino_id(void)
{
	uint32_t id = env_get_ulong("lcd_olinuxino", 10, 0);

	if (id)
		return id;

	if (lcd_olinuxino_eeprom.header == LCD_OLINUXINO_HEADER_MAGIC)
		return lcd_olinuxino_eeprom.id;

	return 0;
}
