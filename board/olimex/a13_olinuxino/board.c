/*
 * Copyright (C) 2020 Olimex Ltd.
 *   Author:  Dimitar Gamishev <hehopmajieh@debian.bg>
 *   Stefan Mavrodiev <stefan@olimex.com>
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
#include <axp_pmic.h>

#include <olimex/boards.h>
#include <olimex/sys_eeprom.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SPL_BUILD
void spl_board_init(void)
{
	int axp_power=0;
	printf("A13 Board no eeprom found!\n ");
	phys_size_t l = 512 * 1024 * 1024;	
	
	axp_power |= axp_init();
	if (!axp_power) {
		printf("PMIC found board is A13-OLinuXino/ A13-OLinuXino WIFI !\n");			
		eeprom->header = OLINUXINO_EEPROM_MAGIC;
		eeprom->id = 4432;
		eeprom->revision.major = 'A';
		eeprom->revision.minor = 0;
	} else {
		if (gd->ram_size == l) {
			printf("PMIC not found board is A13-SOM-512 \n");
	        	eeprom->header = OLINUXINO_EEPROM_MAGIC;
	                eeprom->id = 4788;
                	eeprom->revision.major = 'A';
                	eeprom->revision.minor = 0;			
		} else {
			printf("PMIC not found board is A13-SOM-256/A13-Micro\n");
			eeprom->header = OLINUXINO_EEPROM_MAGIC;
                	eeprom->id = 4787;
                	eeprom->revision.major = 'A';
                	eeprom->revision.minor = 0;
		}

	}
}
#endif /* CONFIG_SPL_BUILD */

#ifdef CONFIG_DISPLAY_BOARDINFO
int show_board_info(void)
{
	char  rev[3];
	const char *name;

	name = olinuxino_get_board_name();

	olinuxino_get_board_revision(rev);
	printf("%-7s%s Rev.%s", "ID:", name, rev);

	return 0;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void)
{
	/*No need to late init*/

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
		return "0:auto";
}
#endif /* CONFIG_ENV_IS_IN_EXT4 */

#ifdef CONFIG_ENV_IS_IN_FAT
const char *env_fat_get_dev_part(void)
{
			return "0:auto";
	
}
#endif /* CONFIG_ENV_IS_IN_FAT */

#if CONFIG_ENV_IS_IN_SPI_FLASH
static enum env_location env_get_location_spi(int prio)
{
	switch (prio) {
	case 0:
		return ENVL_SPI_FLASH;
	case 1:
		return ENVL_EXT4;
	case 2:
		return ENVL_FAT;
	default:
		break;
	}

	return ENVL_UNKNOWN;
}
#endif

static enum env_location env_get_location_default(int prio)
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

enum env_location env_get_location(enum env_operation op, int prio)
{
	uint32_t boot = sunxi_get_boot_device();

	switch (boot) {
	case BOOT_DEVICE_BOARD:
#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
		if (olinuxino_board_has_spi())
			return env_get_location_spi(prio);
		else
#endif
			return env_get_location_default(prio);

#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
	case BOOT_DEVICE_SPI:
		return env_get_location_spi(prio);
#endif

	case BOOT_DEVICE_MMC1:
	case BOOT_DEVICE_MMC2:
		break;

	default:
		break;

	}

	return env_get_location_default(prio);
}
