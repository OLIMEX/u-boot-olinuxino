/*
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 *
 * Copyright (C) 2018 olinuxino Ltd.
 *   Author: Stefan Mavrodiev <stefan@olinuxino.com>
 */
#include <common.h>
#include <i2c.h>
#include <mmc.h>
#include <spl.h>
#include <asm/arch/spl.h>
#include <u-boot/crc.h>

#include <linux/delay.h>
#include <olimex/sys_eeprom.h>

struct olinuxino_eeprom *eeprom = OLINUXINO_EEPROM_DATA;

#if defined(OLINUXINO_EEPROM_BUS)
static int olinuxino_i2c_eeprom_init(void)
{
	int ret;

	if ((ret = i2c_set_bus_num(OLINUXINO_EEPROM_BUS)))
		return ret;

	if ((ret = i2c_probe(0x50)))
		return ret;

	return 0;
}

int olinuxino_i2c_eeprom_read(void)
{
	uint32_t crc;
	int ret;

	if ((ret = olinuxino_i2c_eeprom_init()))
		return ret;

	if ((ret = i2c_read(OLINUXINO_EEPROM_ADDRESS, 0, 1, (uint8_t *)eeprom, 256)))
		return ret;

	if (eeprom->header != OLINUXINO_EEPROM_MAGIC) {
		memset(eeprom, 0xFF, 256);
		return 1;
	}

	crc = crc32(0L, (uint8_t *)eeprom, 252);
	if (eeprom->crc != crc) {
		memset(eeprom, 0xFF, 256);
		return 1;
	}

	return 0;
}

#ifndef CONFIG_SPL_BUILD
int olinuxino_i2c_eeprom_write(void)
{
	uint8_t *data = (uint8_t *)eeprom;
	uint16_t i;
	int ret;

	if ((ret = olinuxino_i2c_eeprom_init())) {
		printf("ERROR: Failed to init eeprom!\n");
		return ret;
	}

	/* Restore magic header */
	eeprom->header = OLINUXINO_EEPROM_MAGIC;

	/* Calculate new chechsum */
	eeprom->crc = crc32(0L, data, 252);

	/* Write new values */
	for(i = 0; i < 256; i += 16) {
		if ((ret = i2c_write(OLINUXINO_EEPROM_ADDRESS, i, 1, data + i , 16))) {
			printf("ERROR: Failed to write eeprom!\n");
			return ret;
		}
		mdelay(5);
	}

	return 0;
}

int olinuxino_i2c_eeprom_erase(void)
{
	uint8_t *data = (uint8_t *)eeprom;
	uint16_t i;
	int ret;

	/* Initialize EEPROM */
	if ((ret = olinuxino_i2c_eeprom_init())) {
		printf("ERROR: Failed to init eeprom!\n");
		return ret;
	}

	/* Erase previous data */
	memset((uint8_t *)eeprom, 0xFF, 256);

	/* Write data */
	for(i = 0; i < 256; i += 16) {
		if ((ret = i2c_write(OLINUXINO_EEPROM_ADDRESS, i, 1, data + i, 16))) {
			printf("ERROR: Failed to write eeprom!\n");
			return ret;
		}
		mdelay(5);
	}

	return 0;
}
#endif /* !CONFIG_SPL_BUILD */
#endif /* OLINUXINO_EEPROM_BUS */

#if defined(OLINUXINO_MMC_SECTOR)
int olinuxino_mmc_eeprom_read(void)
{
	struct mmc *mmc = NULL;
	unsigned long count;
	int ret = 0;

	ret = mmc_initialize(NULL);
	if (ret)
		return ret;

	mmc = find_mmc_device((sunxi_get_boot_device() == BOOT_DEVICE_MMC1) ? 0 : 1);
	if (!mmc)
		return -ENODEV;

	ret = mmc_init(mmc);
	if (ret)
		return ret;

	count = blk_dread(mmc_get_blk_desc(mmc), OLINUXINO_MMC_SECTOR, 1, eeprom);
	if (!count)
		return -EIO;

	return ret;
}

#ifndef CONFIG_SPL_BUILD
int olinuxino_mmc_eeprom_write(void)
{
	struct mmc *mmc = NULL;
	unsigned long count;
	int ret = 0;

	mmc = find_mmc_device((sunxi_get_boot_device() == BOOT_DEVICE_MMC1) ? 0 : 1);
	if (!mmc)
		return -ENODEV;

	ret = mmc_init(mmc);
	if (ret)
		return ret;

	count = blk_dwrite(mmc_get_blk_desc(mmc), OLINUXINO_MMC_SECTOR, 1, eeprom);
	if (!count)
		return -EIO;

	return ret;
}

int olinuxino_mmc_eeprom_erase(void)
{
	struct mmc *mmc = NULL;
	unsigned long count;
	int ret = 0;

	mmc = find_mmc_device((sunxi_get_boot_device() == BOOT_DEVICE_MMC1) ? 0 : 1);
	if (!mmc)
		return -ENODEV;

	ret = mmc_init(mmc);
	if (ret)
		return ret;

	count = blk_derase(mmc_get_blk_desc(mmc), OLINUXINO_MMC_SECTOR, 1);
	if (!count)
		return -EIO;

	return ret;

}
#endif /* !CONFIG_SPL_BUILD */
#endif /* OLINUXINO_MMC_SECTOR */

bool olinuxino_eeprom_is_valid(void)
{
	/*
	 * If checksum during EEPROM initalization was wrong,
	 * then the whole memory location should be empty.
	 * Therefore it's enough to check the magic header
	 */
	return (eeprom->header == OLINUXINO_EEPROM_MAGIC);
}
