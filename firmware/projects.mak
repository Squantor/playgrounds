# SPDX-License-Identifier: MIT
# Copyright (c) 2022 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20220715

# current makefile base dir relative to Makefile
BASE_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

# include all libraries
include $(BASE_DIR)/projects/PC/PC.mak
include $(BASE_DIR)/projects/cortexM0_routines/cortexM0_routines.mak
include $(BASE_DIR)/projects/LPC812M101DH20_e-ink_display/LPC812M101DH20_e-ink_display.mak
include $(BASE_DIR)/projects/LPC812M101DH20_oled_display/LPC812M101DH20_oled_display.mak
include $(BASE_DIR)/projects/LPC812M101DH20_pwm_modulator/LPC812M101DH20_pwm_modulator.mak
include $(BASE_DIR)/projects/LPC845M301HI48_sharp_lcd/LPC845M301HI48_sharp_lcd.mak
include $(BASE_DIR)/projects/systick_template_c/systick_template_c.mak
include $(BASE_DIR)/projects/systick_template_cpp/systick_template_cpp.mak
include $(BASE_DIR)/projects/RP2040_demo/RP2040_demo.mak
include $(BASE_DIR)/projects/RP2040_flash_bringup/RP2040_flash_bringup.mak
include $(BASE_DIR)/projects/RP2040_oled_display/RP2040_oled_display.mak
include $(BASE_DIR)/projects/PC_peripheral_abstraction/PC_peripheral_abstraction.mak
include $(BASE_DIR)/projects/LPC812M101DH20_cpp_prototyping/LPC812M101DH20_cpp_prototyping.mak
include $(BASE_DIR)/projects/RP2040_cpp/RP2040_cpp.mak
include $(BASE_DIR)/projects/LPC812M101DH20_blinky/LPC812M101DH20_blinky.mak
include $(BASE_DIR)/projects/LPC812M101DH20_coro_blinky/LPC812M101DH20_coro_blinky.mak
include $(BASE_DIR)/projects/LPC812M101DH20_nuclone_ADC/LPC812M101DH20_nuclone_ADC.mak
include $(BASE_DIR)/projects/LPC845M301BD48_blinky/LPC845M301BD48_blinky.mak