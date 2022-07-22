# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 202220715

# project settings
NAME := LPC812_pwm_modulator
BOARD := nuclone_LPC812M101DH20
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC812M101DH20

$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project sources
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp

$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
