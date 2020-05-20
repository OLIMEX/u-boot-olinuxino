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

static int board_set_compatible(void *fdt)
{
	char name[64], *p;
	int offset;
	int ret;

	/* Set compatible string */
	snprintf(name, 64, "olimex,%s", olinuxino_get_board_name());
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

static int board_enable_spi_flash(void *fdt)
{
	uint32_t phandle;
	int offset, ret = 0;

	offset = _fdt_path_offset(fdt, "/soc/pinctrl@1c20800");
	if (offset < 0)
		return offset;

	offset = fdt_add_subnode(fdt, offset, "spi0-pc-pins");
	if (offset < 0) {
		printf("%s@%d\n", __func__, __LINE__);
		return offset;
	}

	/* Generate phandle */
	phandle = fdt_create_phandle(fdt, offset);
	if (!phandle) {
		printf("%s@%d\n", __func__, __LINE__);
		return -1;
	}

	ret |= fdt_setprop_string(fdt, offset, "function" , "spi0");
	ret |= fdt_setprop_string(fdt, offset, "pins" , "PC0");
	ret |= fdt_appendprop_string(fdt, offset, "pins", "PC1");
	ret |= fdt_appendprop_string(fdt, offset, "pins", "PC2");
	ret |= fdt_appendprop_string(fdt, offset, "pins", "PC23");
	if (ret < 0) {
		printf("%s@%d\n", __func__, __LINE__);
		return ret;
	}

	offset = _fdt_path_offset(fdt, "/soc/spi@1c05000");
	if (offset < 0)
		return offset;

	/* Change status to okay */
	ret |= fdt_status_okay(fdt, offset);
	ret |= fdt_setprop_u32(fdt, offset, "spi-max-frequency", 20000000);
	ret |= fdt_setprop_u32(fdt, offset, "pinctrl-0", phandle);
	ret |= fdt_setprop_string(fdt, offset, "pinctrl-names", "default");
	if (ret < 0) {
		printf("%s@%d\n", __func__, __LINE__);
		return ret;
	}

	offset = fdt_add_subnode(fdt, offset, "spi-nor@0");
	if (offset < 0) {
		printf("%s@%d\n", __func__, __LINE__);
		return offset;
	}

	ret |= fdt_status_okay(fdt, offset);
	ret |= fdt_setprop_u32(fdt, offset, "spi-max-frequency", 20000000);
	ret |= fdt_setprop_u32(fdt, offset, "reg", 0);
	ret |= fdt_setprop_u32(fdt, offset, "#size-cells", 1);
	ret |= fdt_setprop_u32(fdt, offset, "#address-cells", 1);
	ret |= fdt_setprop_string(fdt, offset, "compatible", "winbond,w25q128");
	ret |= fdt_appendprop_string(fdt, offset, "compatible", "jedec,spi-nor");
	ret |= fdt_appendprop_string(fdt, offset, "compatible", "spi-flash");
	if (ret < 0) {
		printf("%s@%d\n", __func__, __LINE__);
		return ret;
	}

	offset = _fdt_path_offset(fdt, "/aliases");
	if (offset < 0)
		return offset;

	ret = fdt_setprop_string(fdt, offset, "spi0", "/soc/spi@1c05000");
	if (ret < 0)
		printf("%s@%d\n", __func__, __LINE__);

	return ret;
}

static int board_disable_gmac(void *fdt)
{

	return 0;
}

static int board_enable_emac(void *fdt)
{
	return 0;
}

static int board_disable_sdio(void *fdt)
{

	return 0;

}

int board_fix_fdt(void *fdt)
{
 int ret;

        ret = fdt_increase_size(fdt, 4096);
        if (ret)
                return ret;

        ret = board_set_compatible(fdt);
        if (ret)
                return ret;


	return 0;
}
