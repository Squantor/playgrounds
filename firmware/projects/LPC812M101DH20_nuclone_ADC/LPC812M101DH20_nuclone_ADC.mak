# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20230101

# current makefile base dir relative to Makefile
PROJ_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# project settings
NAME := LPC812M101DH20_nuclone_ADC
BOARD := nuclone_LPC812M101DH20
$(NAME)_TARGET := MCU
$(NAME)_MCU := LPC812M101DH20
$(NAME)_DEFINES := 
$(NAME)_LIBS := libMcuLL squantorLibC squantorLibEmbedded
$(NAME)_FILES := $(PROJ_DIR)/src/main.cpp \
$(PROJ_DIR)/src/$(BOARD).cpp \
$(PROJ_DIR)/src/application.cpp \
$(PROJ_DIR)/src/systick.cpp \
$(PROJ_DIR)/src/blinky.cpp \
$(PROJ_DIR)/src/measure.cpp
$(NAME)_INCLUDES := -I$(PROJ_DIR)/inc

# --- nothing user definable below ---
PROJECTS += $(NAME)
$(NAME)_PROJECT_ROOT := $(PROJ_DIR)
$(NAME)_BOARD := $(BOARD)
$(NAME)_DEFINES += -D$(BOARD)
