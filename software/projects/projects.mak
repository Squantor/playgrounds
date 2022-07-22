# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20220715

# current makefile base dir relative to Makefile
PROJECTS_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all libraries
include $(PROJECTS_DIR)/PC/PC.mak
include $(PROJECTS_DIR)/cortexM0_routines/cortexM0_routines.mak
include $(PROJECTS_DIR)/LPC812M101DH20_e-ink_display/LPC812M101DH20_e-ink_display.mak
include $(PROJECTS_DIR)/LPC812M101DH20_oled_display/LPC812M101DH20_oled_display.mak
include $(PROJECTS_DIR)/LPC812M101DH20_pwm_modulator/LPC812M101DH20_pwm_modulator.mak
include $(PROJECTS_DIR)/LPC845M301HI48_sharp_lcd/LPC845M301HI48_sharp_lcd.mak
include $(PROJECTS_DIR)/systick_template_c/systick_template_c.mak
include $(PROJECTS_DIR)/systick_template_cpp/systick_template_cpp.mak