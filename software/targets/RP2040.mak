# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# settings for the LPC812 Microcontroller

# Version: 20220909

# import compiler settings for the core in this microcontroller
include targets/core_CortexM0plus.mak

# Specific C files and linker scripts
FILES += targets/src/RP2040.cpp targets/src/startup.cpp
DEFINES += -DMCU_$(MCU)
LDSCRIPT = -T"targets/ld/RP2040.ld"
