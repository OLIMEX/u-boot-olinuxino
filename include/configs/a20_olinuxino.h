/*
 * Copyright (C) 2020 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */
#ifndef __A20_OLINUXINO_H
#include <configs/sun7i.h>

#define OLINUXINO_EEPROM_BUS		I2C_1
#define OLINUXINO_EEPROM_ADDRESS	0x50
/**
 * If the board has corrupted EEPROM (or it's very old without one)
 * the booted MMC can be used as a backup storage.
 */
#define OLINUXINO_MMC_SECTOR		15

#define LCD_OLINUXINO_EEPROM_BUS	I2C_2
#define LCD_OLINUXINO_EEPROM_ADDRESS	0x50
#endif /* __A20_OLINUXINO_H */
