/**
 * @file    RP2040_boot2.S
 * @brief   Second stage bootloader for RP2040
 */

/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022 Bart Bilos 
 * For conditions of distribution and use, see LICENSE file
 */

.cpu cortex-m0
.thumb

.section .text

.global secondStageBoot
.type secondStageBoot,%function
.thumb_func
secondStageBoot:
  push {lr}
  // TODO: setup XIP
  // TODO: copy SRAM
  // TODO: setup ISR vector table to correct position
  // TODO: set reset vector stack
  // TODO: jump to reset vector
.end