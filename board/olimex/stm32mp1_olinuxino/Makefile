# SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
#
# Copyright (C) 2021, Mitko Gamishev <gamishev@gmail.com>
#

obj-y	+= ../common/sys_eeprom.o
obj-y	+= ../common/boards.o

ifdef CONFIG_SPL_BUILD
obj-y	+= spl.o
else
obj-y	+= ../common/cmd.o
obj-y	+= stm32mp1.o
endif
