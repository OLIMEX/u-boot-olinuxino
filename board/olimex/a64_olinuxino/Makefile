# SPDX-License-Identifier: GPL-2.0+
#
# Makefile
#
# Copyright (C) 2019 Olimex Ltd.
#   Author: Stefan Mavrodiev <stefan@olimex.com>

obj-y	+= board.o
obj-y	+= ../common/sys_eeprom.o
obj-y	+= ../common/sunxi/board.o
obj-y	+= ../common/boards.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_OF_BOARD_FIXUP)	+= fdt.o
obj-$(CONFIG_VIDEO_LCD_OLINUXINO)	+= ../common/cmd.o
obj-$(CONFIG_VIDEO_LCD_OLINUXINO)	+= ../common/lcd_olinuxino.o
endif
