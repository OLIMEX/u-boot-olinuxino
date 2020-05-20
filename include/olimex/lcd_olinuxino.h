/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 */

#ifndef __LCD_OLINUXINO_H
#define __LCD_OLINUXINO_H

#define LCD_OLINUXINO_EEPROM_ADDRESS	0x50
#define LCD_OLINUXINO_HEADER_MAGIC	0x4F4CB727
#define LCD_OLINUXINO_DATA_LEN		256

#define MEDIA_BUS_FMT_RGB666_1X18	0x1009
#define MEDIA_BUS_FMT_RGB888_1X24	0x100a

#define LCD_OLINUXINO_IF_PARALLEL	0
#define LCD_OLINUXINO_IF_LVDS		1

struct lcd_olinuxino_mode {
	u32 pixelclock;
	u32 hactive;
	u32 hfp;
	u32 hbp;
	u32 hpw;
	u32 vactive;
	u32 vfp;
	u32 vbp;
	u32 vpw;
	u32 refresh;
	u32 flags;
};

struct lcd_olinuxino_info {
	char name[32];
	u32 width_mm;
	u32 height_mm;
	u32 bpc;
	u32 bus_format;
	u32 bus_flag;
} __attribute__((__packed__));

struct lcd_olinuxino_eeprom {
	u32 header;
	u32 id;
	char revision[4];
	u32 serial;
	struct lcd_olinuxino_info info;
	u32 num_modes;
	u8 reserved[180];
	u32 checksum;
} __attribute__((__packed__));

extern struct lcd_olinuxino_eeprom lcd_olinuxino_eeprom;

struct lcd_olinuxino_board {
	uint32_t id;
	char compatible[32];
	struct lcd_olinuxino_info info;
	struct lcd_olinuxino_mode mode;
};

extern struct lcd_olinuxino_board lcd_olinuxino_boards[];

bool lcd_olinuxino_is_present(void);

#ifdef CONFIG_VIDEO_SUNXI
char * lcd_olinuxino_video_mode(void);
#endif

#ifdef CONFIG_VIDEO_DE2
int lcd_olinuxino_display_timing(struct display_timing *dt);
#endif

uint32_t lcd_olinuxino_id(void);
uint8_t lcd_olinuxino_interface(void);
struct lcd_olinuxino_board * lcd_olinuxino_get_data(void);

#endif /* __LCD_OLINUXINO_H */
