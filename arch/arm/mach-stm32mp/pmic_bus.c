// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * Sunxi PMIC bus access helpers
 *
 * The axp152 & axp209 use an i2c bus, the axp221 uses the p2wi bus and the
 * axp223 uses the rsb bus, these functions abstract this.
 */

#include <common.h>
#include <command.h>
#include <i2c.h>
#include <dm.h>
#include <power/pmic_bus.h>

#define AXP209_I2C_ADDR			0x34

	struct udevice *dev;

int pmic_bus_init(void)
{
	/* This cannot be 0 because it is used in SPL before BSS is ready */
	static int needs_init = 1;
	__maybe_unused int ret;
	struct udevice *bus;

	if (!needs_init)
		return 0;

	ret = uclass_get_device_by_seq(UCLASS_I2C, 0, &bus);
	if (ret)
		return ret;

	ret = dm_i2c_probe(bus, AXP209_I2C_ADDR, 0, &dev);
	if (ret)
		return ret;

	needs_init = 0;
	return 0;
}

int pmic_bus_read(u8 reg, u8 *data)
{
	return dm_i2c_read(dev, reg, data, 1);
}

int pmic_bus_write(u8 reg, u8 data)
{
	return dm_i2c_write(dev,reg, &data,1);
}

int pmic_bus_setbits(u8 reg, u8 bits)
{
	int ret;
	u8 val;

	ret = pmic_bus_read(reg, &val);
	if (ret)
		return ret;

	if ((val & bits) == bits)
		return 0;

	val |= bits;
	return pmic_bus_write(reg, val);
}

int pmic_bus_clrbits(u8 reg, u8 bits)
{
	int ret;
	u8 val;

	ret = pmic_bus_read(reg, &val);
	if (ret)
		return ret;

	if (!(val & bits))
		return 0;

	val &= ~bits;
	return pmic_bus_write(reg, val);
}
