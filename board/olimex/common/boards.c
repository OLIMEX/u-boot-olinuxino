/*
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */
#include <common.h>

#include <olimex/boards.h>
#include <olimex/sys_eeprom.h>

struct olinuxino_boards olinuxino_boards[] = {
#if defined(CONFIG_TARGET_A20_OLINUXINO)
	/* A20-OLinuXino-Lime */
	{
		OLINUXINO_BOARD_LIME(7739, "A20-OLinuXino-LIME", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(NONE, -1, MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(7743, "A20-OLinuXino-LIME-n4GB", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(NAND, GBYTES(4), MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(8934, "A20-OLinuXino-LIME-n8G", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(NAND, GBYTES(8), MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(9076, "A20-OLinuXino-LIME-s16MB", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(SPI, MBYTES(16), MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(9160, "A20-OLinuXino-LIME-e4GB", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(9516, "A20-OLinuXino-LIME-e16Gs16M", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), MBYTES(512), COM)
	},
	{
		OLINUXINO_BOARD_LIME(9696, "A20-OLinuXino-LIME-e4Gs16M", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), MBYTES(512), COM)
	},

	/* T2-OLinuXino-Lime */
	{
		OLINUXINO_BOARD_LIME(9211, "T2-OLinuXino-LIME-IND", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(NONE, -1, MBYTES(512), IND)
	},
	{
		OLINUXINO_BOARD_LIME(9215, "T2-OLinuXino-LIME-s16MB-IND", "sun7i-a20-olinuxino-lime")
		OLINUXINO_CONFIG(SPI, MBYTES(16), MBYTES(512), IND)
	},
	{
		OLINUXINO_BOARD_LIME(9219, "T2-OLinuXino-LIME-e4G-IND", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), MBYTES(512), IND)
	},
	{
		OLINUXINO_BOARD_LIME(9734, "T2-OLinuXino-LIME-e4Gs16M-IND", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), MBYTES(512), IND)
	},
	{
		OLINUXINO_BOARD_LIME(10481, "T2-OLinuXino-LIME-e8Gs16M-IND", "sun7i-a20-olinuxino-lime-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(1), IND)
	},

	/* A20-OLinuXino-Lime2 */
	{
		OLINUXINO_BOARD_LIME2(7701, "A20-OLinuXino-LIME2", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(8340, "A20-OLinuXino-LIME2-e4GB", "sun7i-a20-olinuxino-lime2-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(9166, "A20-OLinuXino-LIME2-e16GB", "sun7i-a20-olinuxino-lime2-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(7624, "A20-OLinuXino-LIME2-n4GB", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(NAND, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(8910, "A20-OLinuXino-LIME2-n8GB", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(NAND, GBYTES(8), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(8946, "A20-OLinuXino-LIME2-s16M", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(SPI, MBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(9604, "A20-OLinuXino-LIME2-e16Gs16M", "sun7i-a20-olinuxino-lime2-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(9613, "A20-OLinuXino-LIME2-e4Gs16M", "sun7i-a20-olinuxino-lime2-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_LIME2(9905, "A20-OLinuXino-LIME2-G2", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},

	/* T2-OLinuXino-Lime2 */
	{
		OLINUXINO_BOARD_LIME2(9239 , "T2-OLinuXino-LIME2-IND", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_LIME2(9247 , "T2-OLinuXino-LIME2-s16M-IND", "sun7i-a20-olinuxino-lime2")
		OLINUXINO_CONFIG(SPI, MBYTES(16), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_LIME2(9243 , "T2-OLinuXino-LIME2-e8Gs16M-IND", "sun7i-a20-olinuxino-lime2-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(1), IND)
	},

	/* A20-OLinuXino-MICRO */
	{
		OLINUXINO_BOARD_MICRO(4614, "A20-OLinuXino-MICRO", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(4615, "A20-OLinuXino-MICRO-n4GB", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(NAND, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(8661, "A20-OLinuXino-MICRO-e4GB-IND", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(8828, "A20-OLinuXino-MICRO-IND", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(8832, "A20-OLinuXino-MICRO-e4GB", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(8918, "A20-OLinuXino-MICRO-n8G", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(NAND, GBYTES(8), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(9042, "A20-OLinuXino-MICRO-e16G", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(9231, "A20-OLinuXino-MICRO-s16M", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(SPI, MBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(9684, "A20-OLinuXino-MICRO-e4Gs16M", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_MICRO(9689, "A20-OLinuXino-MICRO-e16Gs16M", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},

	/* T2-OLinuXino-MICRO */
	{
		OLINUXINO_BOARD_MICRO(9223, "T2-OLinuXino-MICRO-IND", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(9227, "T2-OLinuXino-MICRO-e4G-IND", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(9235, "T2-OLinuXino-MICRO-s16M-IND", "sun7i-a20-olinuxino-micro")
		OLINUXINO_CONFIG(SPI, MBYTES(16), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(9739, "T2-OLinuXino-MICRO-e4Gs16M-IND", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_MICRO(9789, "T2-OLinuXino-MICRO-e8Gs16M-IND", "sun7i-a20-olinuxino-micro-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(1), IND)
	},

	/* A20-SOM */
	{
		OLINUXINO_BOARD_SOM(4673, "A20-SOM-n4GB", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(NAND, GBYTES(4), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM(7664, "A20-SOM", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM(8849, "A20-SOM-IND", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_SOM(8922, "A20-SOM-n8GB", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(NAND, GBYTES(8), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM(9155, "A20-SOM-e16GB", "sun7i-a20-olimex-som-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM(9148, "A20-SOM-e16GB-IND", "sun7i-a20-olimex-som-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_SOM(9047, "A20-SOM-e16Gs16M", "sun7i-a20-olimex-som-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},

	/* T2-SOM */
	{
		OLINUXINO_BOARD_SOM(9259, "T2-SOM-IND", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_SOM(9827, "T2-SOM-e8Gs16M-IND", "sun7i-a20-olimex-som-evb")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(1), IND)
	},


	/* A20-SOM204 */
	{
		OLINUXINO_BOARD_SOM204(8991, "A20-SOM204-1G", "sun7i-a20-olimex-som204-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM204(8958, "A20-SOM204-1Gs16Me16G-MC", "sun7i-a20-olimex-som204-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD_SOM204(10257, "A20-SOM204-1G-M", "sun7i-a20-olimex-som204-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},

	/* T2-SOM204 */
	{
		OLINUXINO_BOARD_SOM204(10157, "T2-SOM204-1Gs16Me4G-C-I", "sun7i-a20-olimex-som204-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_SOM204(10234, "T2-SOM204-1Gs16Me8G-MC-I", "sun7i-a20-olimex-som204-evb-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(1), IND)
	},
	{
		OLINUXINO_BOARD_SOM204(10238, "T2-SOM204-1G-I", "sun7i-a20-olimex-som204-evb")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), IND)
	},
#endif
#if defined(CONFIG_TARGET_A64_OLINUXINO)
	{
		OLINUXINO_BOARD(8861, "A64-OLinuXino-2Ge8G-IND", "sun50i-a64-olinuxino-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(8), GBYTES(2), IND)
	},
	{
		OLINUXINO_BOARD(9065, "A64-OLinuXino-1Gs16M", "sun50i-a64-olinuxino")
		OLINUXINO_CONFIG(SPI, MBYTES(16), GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD(8367, "A64-OLinuXino-1Ge4GW", "sun50i-a64-olinuxino-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(4), GBYTES(2), COM)
	},
	{
		OLINUXINO_BOARD(8857, "A64-OLinuXino-1G", "sun50i-a64-olinuxino")
		OLINUXINO_CONFIG(NONE, -1, GBYTES(1), COM)
	},
	{
		OLINUXINO_BOARD(9849, "A64-OLinuXino-1Ge16GW", "sun50i-a64-olinuxino-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(2), COM)
	},
	{
		OLINUXINO_BOARD(10728, "A64-OLinuXino-1Ge16GW-EA", "sun50i-a64-olinuxino-emmc")
		OLINUXINO_CONFIG(EMMC, GBYTES(16), GBYTES(2), COM)
	},
#endif
#if defined(CONFIG_TARGET_A13_OLINUXINO)
        {
                OLINUXINO_BOARD(4432, "A13-OLinuXino", "sun5i-a13-olinuxino")
                OLINUXINO_CONFIG(NAND, GBYTES(4), MBYTES(512), COM)
        },
        {
                OLINUXINO_BOARD(4787, "A13-SOM-256", "sun5i-a13-som-256")
                OLINUXINO_CONFIG(NONE, -1, MBYTES(256), COM)
        },
        {
                OLINUXINO_BOARD(4788, "A13-SOM-512", "sun5i-a13-som512")
                OLINUXINO_CONFIG(NONE, -1, MBYTES(512), COM)
        },
#endif
#if defined(CONFIG_TARGET_A10_OLINUXINO)
        {
                OLINUXINO_BOARD(10663, "A10-OLinuXino-LIME-e16Gs16M", "sun4i-a10-olinuxino-lime-emmc")
                OLINUXINO_CONFIG(EMMC, GBYTES(16), MBYTES(512), COM)
        },
        {
                OLINUXINO_BOARD(8950, "A10-OLinuXino-LIME-n8GB", "sun4i-a10-olinuxino-lime-emmc")
                OLINUXINO_CONFIG(EMMC, GBYTES(8), MBYTES(512), COM)
        },
        {
                OLINUXINO_BOARD(4746, "A10-OLinuXino-LIME", "sun4i-a10-olinuxino-lime")
                OLINUXINO_CONFIG(NONE, -1, MBYTES(512), COM)
        },
#endif

	{
		.id = 0,
	}
};

uint32_t olinuxino_get_board_id()
{
	if (!olinuxino_eeprom_is_valid())
		return 0;

	return eeprom->id;
}

const char *olinuxino_get_board_name()
{
	struct olinuxino_boards *board = olinuxino_boards;

	if (!olinuxino_eeprom_is_valid())
		return "";

	while (board->id) {
		if (eeprom->id == board->id)
			return board->name;
		board++;
	}
	return "";
}

void olinuxino_get_board_revision(char *data)
{
	data[0] = 0;

	if (eeprom->revision.major < 'A' || eeprom->revision.major > 'Z')
		return;

	data[0] = eeprom->revision.major;
	data[1] = 0;

	if (eeprom->revision.minor < '1' || eeprom->revision.minor > '9')
		return;

	data[1] = eeprom->revision.minor;
	data[2] = 0;
}

void olinuxino_get_board_mac(char *data)
{
	char *mac = eeprom->mac;

	sprintf(data, "%c%c:%c%c:%c%c:%c%c:%c%c:%c%c",
		(mac[0] == 0xFF) ? 'F' : mac[0],
		(mac[1] == 0xFF) ? 'F' : mac[1],
		(mac[2] == 0xFF) ? 'F' : mac[2],
		(mac[3] == 0xFF) ? 'F' : mac[3],
		(mac[4] == 0xFF) ? 'F' : mac[4],
		(mac[5] == 0xFF) ? 'F' : mac[5],
		(mac[6] == 0xFF) ? 'F' : mac[6],
		(mac[7] == 0xFF) ? 'F' : mac[7],
		(mac[8] == 0xFF) ? 'F' : mac[8],
		(mac[9] == 0xFF) ? 'F' : mac[9],
		(mac[10] == 0xFF) ? 'F' : mac[10],
		(mac[11] == 0xFF) ? 'F' : mac[11]);
}

const char *olinuxino_get_board_fdt()
{
	struct olinuxino_boards *board = olinuxino_boards;

	if (!olinuxino_eeprom_is_valid())
		return "";

	while (board->id) {
		if (eeprom->id == board->id)
			return board->fdt;
		board++;
	}
	return "";

}

bool olinuxino_board_has_spi(void)
{
	if (!olinuxino_eeprom_is_valid())
		return false;

	if (eeprom->config.storage == 's')
		return true;

	/* Some boards have both eMMC and SPI */
	switch (eeprom->id) {
	case 10663:             // A10-OLinuXino-LIME-e16Gs16M
	case 8950:              // A10-OLinuXino-LIME-n8GB
	case 8958:              // A20-SOM204-1Gs16Me16G-MC
	case 10157:             // T2-SOM204-1Gs16Me4G-C-I

	case 9604:              // A20-OLinuXino-LIME2-e16Gs16M
	case 9613:              // A20-OLinuXino-LIME2-e4Gs16M"
	case 9243:              // T2-OLinuXino-LIME2-e8Gs16M-IND

	case 9047:              // A20-SOM-e16Gs16M

	case 9684:              // A20-OLinuXino-MICRO-e4Gs16M
	case 9689:              // A20-OLinuXino-MICRO-e16Gs16M
	case 9739:              // T2-OLinuXino-MICRO-e4Gs16M-IND
	case 9789:              // T2-OLinuXino-MICRO-e4Gs16M-IND

	case 9516:              // A20-OLinuXino-LIME-e16Gs16M
	case 9696:              // A20-OLinuXino-LIME-e4Gs16M
	case 9734:              // T2-OLinuXino-LIME-e4Gs16M-IND
	case 10481:             // T2-OLinuXino-LIME-e8Gs16M-IND
	case 10234:		// T2-SOM204-1Gs16Me8G-MC-I

	case 9827:              // T2-SOM-e8Gs16M-IND
		return true;

	default:
		return false;
	}
}

#if defined(CONFIG_TARGET_A20_OLINUXINO)
enum olinuxino_family olinuxino_get_board_family()
{
	struct olinuxino_boards *board = olinuxino_boards;

	if (!olinuxino_eeprom_is_valid())
		return OLINUXINO_UNKNOWN;

	while (board->id) {
		if (eeprom->id == board->id)
			return board->family;
		board++;
	}

	return OLINUXINO_UNKNOWN;
}

enum olinuxino_phy_mode olinuxino_get_phy_mode(void)
{
	switch (olinuxino_get_board_family()) {
		case OLINUXINO_UNKNOWN:
			return OLINUXINO_PHY_MODE_UNKNOWN;

		case OLINUXINO_MICRO:
		case OLINUXINO_LIME:
			return OLINUXINO_PHY_MODE_MII;

		default:
			return OLINUXINO_PHY_MODE_RGMII;
	}
}

uint8_t olinuxino_phy_txdelay()
{
	switch (olinuxino_get_board_family()) {
	case OLINUXINO_LIME2:
		if (eeprom->revision.major > 'G')
			/* KSZ9031 */
			return 4;
		else if (eeprom->revision.major > 'E')
			/* RTL8211E */
			return 2;
		else
			return 0;
	case OLINUXINO_SOM:
	case OLINUXINO_SOM204:
		return 4;
	default:
		return 0;
	}
}

bool olinuxino_board_has_emac()
{
	if (!olinuxino_eeprom_is_valid())
		return false;

	switch (eeprom->id) {
	/* A20-SOM204-1Gs16Me16G-MC */
	case 8958:
	/* A20-SOM204-1G-M */
	case 10257:
	/* T2-SOM204-1Gs16Me8G-MC-I */
	case 10234:
		return true;

	default:
		return false;
	}
}
#endif

#ifdef CONFIG_TARGET_A64_OLINUXINO
#include <asm/io.h>
#include <asm/arch/gpio.h>
uint8_t olinuxino_phy_rst_pin(void)
{
	u32 reg;

	/* Make sure PD24 is input */
	sunxi_gpio_set_cfgpin(SUNXI_GPD(24), SUNXI_GPIO_INPUT);
	reg = readl(0x01c2087c);

	return ((reg >> 24) & 0x01);
}
#endif

#ifdef CONFIG_VIDEO_LCD_OLINUXINO
const char * olinuxino_get_lcd_pwr_pin()
{
#if defined(CONFIG_TARGET_A20_OLINUXINO)
	switch (olinuxino_get_board_family()) {
	case OLINUXINO_SOM:
		return "PH7";
	case OLINUXINO_SOM204:
		return "PC24";
	default:
		return "PH8";
	}
#elif defined(CONFIG_TARGET_A33_OLINUXINO)
	return "PB2";
#elif defined(CONFIG_TARGET_A64_OLINUXINO)
	return "PD23";
#else
	return "";
#endif
}

const char * olinuxino_get_lcd_pwm_pin()
{
#if defined(CONFIG_TARGET_A20_OLINUXINO)
	return "PB2";
#elif defined(CONFIG_TARGET_A33_OLINUXINO)
	return "PH0";
#elif defined(CONFIG_TARGET_A64_OLINUXINO)
	return "PD22";
#else
	return "";
#endif
}

const char *olinuxino_get_lcd_irq_pin()
{
#if defined(CONFIG_TARGET_A20_OLINUXINO)
	switch (olinuxino_get_board_family()) {
	case OLINUXINO_LIME2:
		return "PH10";
	case OLINUXINO_SOM:
		return NULL;
	case OLINUXINO_SOM204:
		return "PH2";
	default:
		return "PH12";
	}
#elif defined(CONFIG_TARGET_A33_OLINUXINO)
	return "PB5";
#elif defined(CONFIG_TARGET_A64_OLINUXINO)
	return "PH7";
#else
	return "";
#endif
}

const char *olinuxino_get_lcd_rst_pin()
{
#if defined(CONFIG_TARGET_A20_OLINUXINO)
switch (olinuxino_get_board_family()) {
	case OLINUXINO_LIME2:
		return "PH11";
	case OLINUXINO_SOM:
		return NULL;
	case OLINUXINO_SOM204:
		return "PI1";
	default:
		return "PB13";
	}
#elif defined(CONFIG_TARGET_A33_OLINUXINO)
	return "PB6";
#elif defined(CONFIG_TARGET_A64_OLINUXINO)
	return "PH8";
#endif
}
#endif /* CONFIG_VIDEO_LCD_OLINUXINO */
