/*
 * Copyright (C) 2020 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */

#include <common.h>
#include <env_internal.h>
#include <mmc.h>
#include <spl.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mmc.h>
#include <asm/arch/spl.h>
#include <asm/gpio.h>

#include <olimex/boards.h>
#include <olimex/sys_eeprom.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SPL_BUILD
void spl_board_init(void)
{
	uint32_t bootdev;

	printf("Loading configuration from EEPROM: ");

	if (!olinuxino_i2c_eeprom_read()) {
		printf("OK\n");
		printf("Verifying data: ");

		if (olinuxino_eeprom_is_valid()) {
			printf("OK\n");
			return;
		}
		printf("Error\n");
	}
	printf("Error\n");

	/* If booted from eMMC/MMC try loading configuration */
	bootdev = spl_boot_device();
	if (bootdev == BOOT_DEVICE_MMC1 || bootdev == BOOT_DEVICE_MMC2) {
		printf("Loading configuration from MMC: ");
		if (!olinuxino_mmc_eeprom_read()) {
			printf("OK\n");
			printf("Verifying data: ");

			if (olinuxino_eeprom_is_valid()) {
				printf("OK\n");
				return;
			}
			printf("Error\n");
		}
		printf("Error\n");
	}

	printf("\nWARNING: The board cannot be detected!\n");
	printf("Please run:\n");
	printf("\t\'olinuxino config list\' - Select your board\n");
	printf("\t\'olinuxino config write\' - Store the board configuration\n");
	printf("\t\'reset\' - Reset the board and load the configuration\n");
	printf("\nUsing \'A20-OLinuXino-LIME\' as fallback configuration.\n\n");

	eeprom->header = OLINUXINO_EEPROM_MAGIC;
	eeprom->id = 7739;
	eeprom->revision.major = 'A';
	eeprom->revision.minor = 0;
	eeprom->serial = 0;
	memset(eeprom->mac, 0xFF, 12);
}
#endif /* CONFIG_SPL_BUILD */

#ifdef CONFIG_DISPLAY_BOARDINFO
int show_board_info(void)
{
	char mac[17], rev[3];
	const char *name;

	/**
	 * In case of lowercase revision number, rewrite eeprom
	 */
	if (eeprom->revision.major >= 'a' && eeprom->revision.major <= 'z') {
		eeprom->revision.major -= 0x20;

		olinuxino_i2c_eeprom_write();
	}

	/* Get board name and compare if with eeprom content */
	name = olinuxino_get_board_name();

	olinuxino_get_board_revision(rev);
	printf("%-7s%s Rev.%s", "ID:", name, rev);
	printf("\n%-7s%08X\n", "SN:", eeprom->serial);

	olinuxino_get_board_mac(mac);
	printf("%-7s%s\n", "MAC:", mac);

	return 0;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void)
{
	enum olinuxino_family family = olinuxino_get_board_family();
	int pin;

	if (family == OLINUXINO_MICRO)
 		pin = sunxi_name_to_gpio("PB8");
	else
		pin = sunxi_name_to_gpio("PC3");

	gpio_request(pin, "satapwr");
	gpio_direction_output(pin, 1);
	/* Give attached sata device time to power-up to avoid link timeouts */
	mdelay(500);

	/*
	 * A20-SOM204 needs manual reset for rt8723bs chip
	 */
	if (family == OLINUXINO_SOM204) {
		pin = sunxi_name_to_gpio("PB11");
		gpio_request(pin, "btpwr");
		gpio_direction_output(pin, 0);
		mdelay(100);
		gpio_direction_output(pin, 1);

		/* Reset LAN8710 */
		pin = sunxi_name_to_gpio("PC18");
		gpio_request(pin, "emac_rst");
		gpio_direction_output(pin, 0);

		if (olinuxino_get_board_id() == 10257) {
			mdelay(100);
			gpio_direction_output(pin, 1);
		}
	}

	return 0;
}
#endif /* CONFIG_BOARD_LATE_INIT */

#ifdef CONFIG_MULTI_DTB_FIT
int board_fit_config_name_match(const char *name)
{
	const char *dtb = olinuxino_get_board_fdt();

	return (!strncmp(name, dtb, strlen(dtb))) ? 0 : -1;
}
#endif /* CONFIG_MULTI_DTB_FIT */

#ifdef CONFIG_ENV_IS_IN_EXT4
const char *env_ext4_get_dev_part(void)
{
	switch (sunxi_get_boot_device()) {
	case BOOT_DEVICE_BOARD:
	case BOOT_DEVICE_SPI:
		if (eeprom->config.storage == 'e')
			return "1:auto";
		else
			return "0:auto";
	case BOOT_DEVICE_MMC1:
		return "0:auto";
	case BOOT_DEVICE_MMC2:
		return "1:auto";
	default:
		return CONFIG_ENV_EXT4_DEVICE_AND_PART;
	}
}
#endif /* CONFIG_ENV_IS_IN_EXT4 */

#ifdef CONFIG_ENV_IS_IN_FAT
const char *env_fat_get_dev_part(void)
{
	switch (sunxi_get_boot_device()) {
	case BOOT_DEVICE_BOARD:
	case BOOT_DEVICE_SPI:
		if (eeprom->config.storage == 'e')
			return "1:auto";
		else
			return "0:auto";
	case BOOT_DEVICE_MMC1:
		return "0:auto";
	case BOOT_DEVICE_MMC2:
		return "1:auto";
	default:
		return CONFIG_ENV_FAT_DEVICE_AND_PART;
	}
}
#endif /* CONFIG_ENV_IS_IN_FAT */

#if defined(CONFIG_ENV_IS_IN_EXT4) && defined(CONFIG_ENV_IS_IN_FAT)
enum env_location env_get_location(enum env_operation op, int prio)
{
	switch (prio) {
	case 0:
		return ENVL_EXT4;
	case 1:
		return ENVL_FAT;
	default:
		break;
	}

	return ENVL_UNKNOWN;
}
#endif
