/**
 * @file    RP2040_boot2.S
 * @brief   Second stage bootloader for RP2040
 */

/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022 Bart Bilos 
 * For conditions of distribution and use, see LICENSE file
 */

// general settings
#define CMD_READ 0x03 /*!< SPI flash read command */
#define ADDR_LEN 6  /*!< Address length (in 4bit increments) */

// RP2040 memory locations
#define XIP_SSI_BASE  (0x18000000)
#define XIP_BASE      (0x10000000)
#define PPB_BASE      (0xe0000000)
#define SRAM4_BASE    (0x20040000)
#define SRAM5_BASE    (0x20041000)

// RP2040 register offsets
#define SSI_CTRLR0_OFFSET     (0x00)
#define SSI_CTRLR1_OFFSET     (0x04)
#define SSI_SSIENR_OFFSET     (0x08)
#define SSI_BAUDR_OFFSET      (0x14)
#define SSI_SPI_CTRLR0_OFFSET (0xf4)
#define M0PLUS_VTOR_OFFSET    (0xed08)

// RP2040 register settings
#define PICO_FLASH_SPI_CLKDIV 0
#define CTRLR0_XIP (0x0 << 21) | (31 << 16) | (0x3 << 8)
#define CTRLR1_XIP 0
#define SPI_CTRLR0_XIP (CMD_READ << 24) | (2 << 8) | (ADDR_LEN << 2)

.cpu cortex-m0
.thumb

.section .boot.entry, "ax"

.global secondStageBoot
.type secondStageBoot,%function
.thumb_func
secondStageBoot:

  // Use r3 as base address where possible
  ldr r3, =XIP_SSI_BASE

  // Disable SSI to allow further config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // Set baud rate
  mov r1, #PICO_FLASH_SPI_CLKDIV
  str r1, [r3, #SSI_BAUDR_OFFSET]

  // configure XIP
  ldr r1, =(CTRLR0_XIP)
  str r1, [r3, #SSI_CTRLR0_OFFSET]

  ldr r1, =(SPI_CTRLR0_XIP)
  ldr r0, =(XIP_SSI_BASE + SSI_SPI_CTRLR0_OFFSET)
  str r1, [r0]

  // NDF=0 (single 32b read)
  mov r1, #CTRLR1_XIP
  str r1, [r3, #SSI_CTRLR1_OFFSET]

  // Re-enable SSI
  mov r1, #1
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // flash is now mapped into memory space, we can now run from it

  // setup ISR vector table to correct position in VTOR of the PPB
  ldr r0, =(XIP_BASE + 0x100)
  ldr r1, =(PPB_BASE + M0PLUS_VTOR_OFFSET)
  str r0, [r1]
  ldmia r0, {r0, r1}  // load stack pointer in R0 and entry from vectors in R1
  msr msp, r0         // load main stack pointer with reset vector value
  bx r1               // jump to reset vector

.global literals
literals:
.ltorg

.end