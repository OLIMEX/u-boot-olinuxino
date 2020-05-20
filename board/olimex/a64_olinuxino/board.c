/*
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */

#include <common.h>
#include <mmc.h>
#include <asm/arch/gpio.h>
#include <asm/arch/spl.h>
#include <asm/gpio.h>

#include <dm/uclass.h>
#include <dm/device-internal.h>

#include <olimex/boards.h>
#include <olimex/lcd_olinuxino.h>
#include <olimex/sys_eeprom.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_SPL_BUILD
void spl_board_init(void)
{
	struct mmc *mmc = NULL;

	/* Make sure ram is empty */
	memset((void *)eeprom, 0xFF, 256);

	/**
	 * The magic header is needed for validating the configuration
	 */
	eeprom->header = OLINUXINO_EEPROM_MAGIC;

	/**
	 * Try some detection:
	 *
	 * 1. If RAM > 1G, then A64-OLinuXino-2Ge8G-IND
	 * 2. If SPI is present, then A64-OLinuXino-1Gs16M
	 * 3. If eMMC is present, then A64-OLinuXino-1Ge4GW
	 * 4. Else -> A64-OLinuXino-1G
	 */
	if ((int)(gd->ram_size >> 20) > 1024) {
		eeprom->id = 8861;
		eeprom->config.storage = 'e';
		return;
	}

	if (sunxi_spi_is_present()) {
		eeprom->id = 9065;
		eeprom->config.storage = 's';
		return;
	}

	/*Drop eMMC size detection */
	/*
	mmc_initialize(NULL);
	mmc = find_mmc_device(1);
	if (!mmc_init(mmc)) {
		if ((mmc->capacity >> 30) > 4)
			eeprom->id = 9849;
		else
			eeprom->id = 8367;
		eeprom->config.storage = 'e';
		return;
	}

	*/
	eeprom->config.storage = 'e';
	eeprom->id = 8367;
}
#endif

#ifdef CONFIG_LAST_STAGE_INIT
#ifdef CONFIG_VIDEO_LCD_OLINUXINO
static void olinuxino_enable_panel(void)
{
	struct lcd_olinuxino_board *lcd = lcd_olinuxino_get_data();
	int pin;

	pin = sunxi_name_to_gpio("PD22");
	if (pin >= 0) {
		gpio_request(pin, "lcd_backlight_pwm");

		if (lcd->id == 7894)
			gpio_direction_output(pin, 1);
		else
			gpio_direction_output(pin, 0);
	}

	pin = sunxi_name_to_gpio("PD23");
	if (pin >= 0) {
		gpio_request(pin, "lcd_power");
		gpio_direction_output(pin, 1);
	}
}
#endif /* CONFIG_VIDEO_LCD_OLINUXINO */
int last_stage_init(void)
{
	struct udevice *dev;
	int ret;

#ifdef CONFIG_USB_MUSB_GADGET
	ret = uclass_first_device(UCLASS_USB_GADGET_GENERIC, &dev);
	if (!dev || ret) {
		printf("No USB device found\n");
		return 0;
	}

	ret = device_probe(dev);
	if (ret) {
		printf("Failed to probe USB device\n");
		return 0;
	}
#endif

#ifdef CONFIG_VIDEO_LCD_OLINUXINO
	if (olinuxino_phy_rst_pin() == 0)
		olinuxino_enable_panel();
#endif

	return 0;
}
#endif
