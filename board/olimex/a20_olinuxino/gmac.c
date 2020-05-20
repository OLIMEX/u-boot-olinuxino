/*
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */
#include <common.h>
#include <netdev.h>
#include <miiphy.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/gpio.h>

#include <olimex/boards.h>

void eth_init_board(void)
{
	static struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	enum olinuxino_phy_mode mode;
	uint8_t tx_delay = 0;
	int pin;

	/**
	 * A20-SOM204-1G-M (10257) has only megabit interface
	 */
	if (olinuxino_get_board_id() == 10257)
		return;

	mode = olinuxino_get_phy_mode();
	if (mode == OLINUXINO_PHY_MODE_UNKNOWN)
		return;

	tx_delay = olinuxino_phy_txdelay();

	/* Set up clock gating */
	setbits_le32(&ccm->ahb_gate1, 0x1 << AHB_GATE_OFFSET_GMAC);

	if (mode == OLINUXINO_PHY_MODE_RGMII) {
		setbits_le32(&ccm->gmac_clk_cfg,
			     CCM_GMAC_CTRL_TX_CLK_DELAY(tx_delay));
		setbits_le32(&ccm->gmac_clk_cfg,
			     CCM_GMAC_CTRL_TX_CLK_SRC_INT_RGMII |
			     CCM_GMAC_CTRL_GPIT_RGMII);
	} else {
		setbits_le32(&ccm->gmac_clk_cfg,
			     CCM_GMAC_CTRL_TX_CLK_SRC_MII |
			     CCM_GMAC_CTRL_GPIT_MII);
	}

	/* Configure pins for GMAC */
	for (pin = SUNXI_GPA(0); pin <= SUNXI_GPA(16); pin++) {

		/* skip unused pins in RGMII mode */
		if (mode == OLINUXINO_PHY_MODE_RGMII ) {
			if (pin == SUNXI_GPA(9) || pin == SUNXI_GPA(14))
				continue;
		}

		sunxi_gpio_set_cfgpin(pin, SUN7I_GPA_GMAC);
		sunxi_gpio_set_drv(pin, 3);
	}

	/* A20-OLinuXino-MICRO needs additional signal for TXERR */
	if (olinuxino_get_board_family() == OLINUXINO_MICRO) {
		sunxi_gpio_set_cfgpin(SUNXI_GPA(17),  SUN7I_GPA_GMAC);
	}
}
