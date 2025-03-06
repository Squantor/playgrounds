# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := turboc_test
$(NAME)_TARGET := TURBOC
$(NAME)_DEFINES := 
$(NAME)_LIBS :=
$(NAME)_FILES := $(PROJ_DIR)/src/main.c \
$(PROJ_DIR)/src/test.c
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc
$(NAME)_PREBUILD_SCRIPT := $(PROJ_DIR)/prebuild.sh
$(NAME)_POSTBUILD_SCRIPT := $(PROJ_DIR)/postbuild.sh

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
