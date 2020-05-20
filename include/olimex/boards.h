/*
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 *
 * List of all supported devices
 *
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 */
#ifndef __BOARDS_H
#define __BOARDS_H

enum olinuxino_storage {
	STORAGE_NONE = 0,
	STORAGE_EMMC = 'e',
	STORAGE_NAND = 'n',
	STORAGE_SPI = 's'
};

enum olinuxino_grade {
	GRADE_COM = 0,
	GRADE_IND = 1,
};

enum olinuxino_sizes {
	S_1 = 0, S_2, S_4, S_8, S_16, S_32, S_64, S_128, S_256, S_512
};

#if defined(CONFIG_TARGET_A20_OLINUXINO)
enum olinuxino_family {
	OLINUXINO_UNKNOWN = 0,
	OLINUXINO_MICRO,
	OLINUXINO_LIME,
	OLINUXINO_LIME2,
	OLINUXINO_SOM,
	OLINUXINO_SOM204,
};

enum olinuxino_phy_mode {
	OLINUXINO_PHY_MODE_RGMII = 0,
	OLINUXINO_PHY_MODE_MII,
	OLINUXINO_PHY_MODE_UNKNOWN,
};
#endif

#define BYTES(a)	(S_##a )
#define KBYTES(a)	(S_##a + 10)
#define MBYTES(a)	(S_##a + 20)
#define GBYTES(a)	(S_##a + 30)

#define OLINUXINO_CONFIG(_storage, _size, _ram, _grade) \
	.config = { STORAGE_##_storage, _size, _ram, GRADE_##_grade },

#define OLINUXINO_BOARD(_id, _name, _fdt) \
	.id = _id, \
	.name = _name, \
	.fdt = _fdt,

#if defined(CONFIG_TARGET_A20_OLINUXINO)
#define OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, _family) \
	OLINUXINO_BOARD(_id, _name, _fdt) \
	.family = _family,

#define OLINUXINO_BOARD_MICRO(_id, _name, _fdt) \
	OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, OLINUXINO_MICRO)

#define OLINUXINO_BOARD_LIME(_id, _name, _fdt) \
	OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, OLINUXINO_LIME)

#define OLINUXINO_BOARD_LIME2(_id, _name, _fdt) \
	OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, OLINUXINO_LIME2)

#define OLINUXINO_BOARD_SOM(_id, _name, _fdt) \
	OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, OLINUXINO_SOM)

#define OLINUXINO_BOARD_SOM204(_id, _name, _fdt) \
	OLINUXINO_BOARD_FAMILY(_id, _name, _fdt, OLINUXINO_SOM204)
#endif


struct olinuxino_boards {
	uint32_t id;
	const char name[64];
	const char fdt[64];
#if defined(CONFIG_TARGET_A20_OLINUXINO)
	enum olinuxino_family family;
#endif
	uint8_t config[4];
};

extern struct olinuxino_boards olinuxino_boards[];

uint32_t olinuxino_get_board_id(void);
const char *olinuxino_get_board_name(void);
void olinuxino_get_board_revision(char *data);
void olinuxino_get_board_mac(char *data);
const char *olinuxino_get_board_fdt(void);
bool olinuxino_board_has_spi(void);

#if defined(CONFIG_TARGET_A20_OLINUXINO)
enum olinuxino_family olinuxino_get_board_family(void);
enum olinuxino_phy_mode olinuxino_get_phy_mode(void);
uint8_t olinuxino_phy_txdelay(void);
bool olinuxino_board_has_emac(void);
#endif

#if defined(CONFIG_TARGET_A64_OLINUXINO)
uint8_t olinuxino_phy_rst_pin(void);
#endif

#ifdef CONFIG_VIDEO_LCD_OLINUXINO
const char *olinuxino_get_lcd_pwm_pin(void);
const char *olinuxino_get_lcd_pwr_pin(void);
const char *olinuxino_get_lcd_irq_pin(void);
const char *olinuxino_get_lcd_rst_pin(void);
#endif

#endif /* __BOARDS_H */
