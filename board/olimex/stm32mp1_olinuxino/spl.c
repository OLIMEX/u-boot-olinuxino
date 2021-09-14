// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (C) 2018, STMicroelectronics - All Rights Reserved
 */

#include <config.h>
#include <common.h>
#include <init.h>
#include <asm/io.h>
#include <asm/arch/sys_proto.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <axp_pmic.h>

/* board early initialisation in board_f: need to use global variable */
static u32 opp_voltage_mv __section(".data");

void board_vddcore_init(u32 voltage_mv)
{
//	if (IS_ENABLED(CONFIG_PMIC_STPMIC1) && CONFIG_IS_ENABLED(POWER_SUPPORT))
		opp_voltage_mv = voltage_mv;
}

int board_early_init_f(void)
{

		printf("Init AXP209 PMIC \n");

		printf("VDD Core set to: %d mv \n",opp_voltage_mv);
		int ret;

		ret = axp_init();
		ret = axp_set_aldo3(1200);
		ret = axp_set_dcdc2(opp_voltage_mv);
		mdelay(100);
		if (ret)
			printf("AXP Init Failed \n");
		printf("---------%d------------\n",ret);


	return 0;
}

#ifdef CONFIG_DEBUG_UART_BOARD_INIT
void board_debug_uart_init(void)
{
#if (CONFIG_DEBUG_UART_BASE == STM32_UART4_BASE)

#define RCC_MP_APB1ENSETR (STM32_RCC_BASE + 0x0A00)
#define RCC_MP_AHB4ENSETR (STM32_RCC_BASE + 0x0A28)

	/* UART4 clock enable */
	setbits_le32(RCC_MP_APB1ENSETR, BIT(16));

#define GPIOG_BASE 0x50008000
	/* GPIOG clock enable */
	writel(BIT(6), RCC_MP_AHB4ENSETR);
	/* GPIO configuration for ST boards: Uart4 TX = G11 */
	writel(0xffbfffff, GPIOG_BASE + 0x00);
	writel(0x00006000, GPIOG_BASE + 0x24);
#else

#error("CONFIG_DEBUG_UART_BASE: not supported value")

#endif
}
#endif
