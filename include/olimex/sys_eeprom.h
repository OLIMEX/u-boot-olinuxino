/*
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 *
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 */
#ifndef __SYS_EEPROM_H
#define __SYS_EEPROM_H

/**
 * Location in the RAM.
 * Content should be transfered after relocation
 */
#define OLINUXINO_EEPROM_DATA ((struct olinuxino_eeprom *)(CONFIG_SYS_SDRAM_BASE))
extern struct olinuxino_eeprom *eeprom;

/**
 * The content of has magic header
 */
#define OLINUXINO_EEPROM_MAGIC		0x4f4caa55

/**
 * Define eeprom structure
 */
struct olinuxino_eeprom {
	uint32_t header;
	uint32_t id;
	struct {
		char major;
		char minor;
	} revision;
	uint32_t serial;
	struct {
		uint8_t storage;
		uint8_t size;
		uint8_t ram;
		uint8_t grade;
	} config;
	char mac[12];
	uint8_t reserved[222];
	uint32_t crc;
} __attribute__ ((__packed__));

#if defined(OLINUXINO_EEPROM_BUS)
/* I2C access functions */
int olinuxino_i2c_eeprom_read(void);
int olinuxino_i2c_eeprom_write(void);
int olinuxino_i2c_eeprom_erase(void);
#endif

#if defined(OLINUXINO_MMC_SECTOR)
/* Raw MMC access function */
int olinuxino_mmc_eeprom_read(void);
int olinuxino_mmc_eeprom_write(void);
int olinuxino_mmc_eeprom_erase(void);
#endif

bool olinuxino_eeprom_is_valid(void);

#endif	/* __SYS_EEPROM_H */
