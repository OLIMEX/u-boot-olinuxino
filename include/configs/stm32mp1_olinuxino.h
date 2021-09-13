/* SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause */
/*
 * Copyright (C) 2020 Marek Vasut <marex@denx.de>
 *
 * Configuration settings for the DH STM32MP15x SoMs
 */

#ifndef __CONFIG_STM32MP1_OLINUXINO_H__
#define __CONFIG_STM32MP1_OLINUXINO_H__

#include <configs/stm32mp1.h>

//#define CONFIG_SPL_TARGET		"u-boot.itb"
#define OLINUXINO_EEPROM_BUS 0
#define OLINUXINO_EEPROM_ADDRESS 0x50
#endif
