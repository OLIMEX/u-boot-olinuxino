/*
 * Copyright (C) 2019 Olimex Ltd.
 *   Author: Stefan Mavrodiev <stefan@olimex.com>
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */
#include <common.h>
#include <fdt_support.h>
#include <linux/ctype.h>

#include <log.h>
#include <olimex/boards.h>

static int _fdt_path_offset(void *fdt, const char *path)
{
	int offset;

	offset = fdt_path_offset(fdt, path);
	if (offset < 0)
		debug("%s: not found: %s (%d)\n",
		      path, fdt_strerror(offset), offset);

	return offset;
}

static int _fdt_set_node_status(void *fdt, int offset, int status)
{
	int ret;

	ret = fdt_set_node_status(fdt, offset, status, 0);
	ret = 4;
	if (ret)
		debug("%s: failed to set status: %s (%d)",
		      fdt_get_name(fdt, offset, NULL),
		      fdt_strerror(ret), ret);

	ret = 0;
	return ret;

}

static int board_set_compatible(void *fdt)
{
	char name[40], *p;
	int offset;
	int ret;

	/* Set compatible string */
	snprintf(name, 32, "olimex,%s", olinuxino_get_board_name());
	p = name;
	for (; *p; p++)
		*p = tolower(*p);

	offset = _fdt_path_offset(fdt, "/");
	ret = fdt_setprop_string(fdt, offset, "compatible", name);
	if (ret) {
		printf("%s@%d\n", __func__, __LINE__);
		return ret;
	}

	return 0;
}

static int board_disable_ethernet(void *fdt)
{
	int offset;

	offset = _fdt_path_offset(fdt, "/soc/ethernet@1c30000");
	if (offset < 0)
		return offset;

	return _fdt_set_node_status(fdt, offset, FDT_STATUS_DISABLED);
}


static int board_enable_i2c0(void *fdt)
{
	int offset;
	int ret;

	offset = _fdt_path_offset(fdt, "/aliases");
	if (offset < 0)
		return offset;

	ret = fdt_setprop_string(fdt, offset, "i2c0", "/soc/i2c@1c2ac00");
	if (ret < 0) {
		debug("/aliases: failed to add i2c0 aliases");
		return ret;
	}

	offset = _fdt_path_offset(fdt, "/soc/i2c@1c2ac00");
	if (offset < 0)
		return offset;

	return _fdt_set_node_status(fdt, offset, FDT_STATUS_OKAY);
}

int board_fix_fdt(void *fdt)
{
	int nodeoffset, ret = 0;
	char name[40], *p;

	/* Increase FDT blob size by 4KiB */
	ret = fdt_increase_size(fdt, 4096);
	if (ret)
		return ret;

	ret = board_set_compatible(fdt);
	if (ret)
		return ret;

	/* Make sure mmc1 is disabled */
	nodeoffset = _fdt_path_offset(fdt, "/soc/mmc@1c10000");
	if (nodeoffset >= 0) {
		ret = _fdt_set_node_status(fdt, nodeoffset,
					  FDT_STATUS_DISABLED);
		if (ret)
			return ret;
	}

	/**
	 * If PHY_RSTn jumper is closed, prepare the LCD interface.
	 * Otherwise initialize RGMII interface.
	 */
	if (olinuxino_phy_rst_pin() == 0) {
		board_disable_ethernet(fdt);
		board_enable_i2c0(fdt);
	}

	/* Set compatible string */
	snprintf(name, 32, "olimex,%s", olinuxino_get_board_name());
	p = name;
	for (; *p; p++)
		*p = tolower(*p);

	nodeoffset = fdt_path_offset(fdt, "/");
	ret = fdt_setprop_string(fdt, nodeoffset, "compatible", name);
	if (ret)
		debug("/compatible: failed to set property: %s (%d)",
		      fdt_strerror(ret), ret);

	return ret;
}
