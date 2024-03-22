# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20220715

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all libraries
include $(BASE_DIR)/projects/PC/PC.mak
include $(BASE_DIR)/projects/PC_peripheral_abstraction/PC_peripheral_abstraction.mak
include $(BASE_DIR)/projects/include_test/include_test.mak
include $(BASE_DIR)/projects/sqminunit_cpp/sqminunit_cpp.mak
