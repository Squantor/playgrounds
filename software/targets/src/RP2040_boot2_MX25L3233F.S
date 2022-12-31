/**
 * @file    RP2040_boot2_MX25L3233F.S
 * @brief   RP2040 second stage bootloader for MX25L3233F
 */

/**
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2022 Bart Bilos 
 * For conditions of distribution and use, see LICENSE file
 */

#include <RP2040_defs.h>

#define CMD_READ 0x6B         /**< MX25L3233F flash read command */
#define CMD_READ_STATUS 0x05  /**< MX25L3233F read status register */
#define CMD_WRITE_ENABLE 0x06 /**< MX25L3233F write enable */
#define CMD_WRITE_STATUS 0x01 /**< MX25L3233F write status and configuration registers */

#define STATUS_WEL_BITS (1<<1) /**< MX25L3233F write latch enable bit */
#define STATUS_QE_BITS (1<<6) /**< MX25L3233F write latch enable bit */

#define ADDR_LEN 6           /**< Address length (in 4bit increments) */

// RP2040 register settings
#define PICO_FLASH_SPI_CLKDIV 2

// SSI CTRLR0 setting for SPI: standard SPI format, 8bit dataframe, TX/RX read mode
#define CTRLR0_SPI (7 << 16) | (0 << 8)
// SSI CTRLR0 setting for XIP: Quad SPI format, 32bit dataframe, EEPROM read mode
#define CTRLR0_XIP (0x2 << 21) | (31 << 16) | (0x3 << 8)
// SSI CTRLR1 setting for XIP:
#define CTRLR1_XIP 0                                     
// SSI SPI CTRL0 setting for XIP: 8 wait cycles, 8 bit instruction, 24 bit address (6*4), cmd and address normal
#define SPI_CTRLR0_XIP (CMD_READ << 24) | (8 << 11) | (2 << 8) | (ADDR_LEN << 2) | (0x0 << 0)

.cpu cortex-m0
.thumb

.section .boot.entry, "ax"

.global secondStageBoot
.type secondStageBoot,%function
.thumb_func
secondStageBoot:
  // Use r3 as SSI base address 
  ldr r3, =XIP_SSI_BASE

  // setup SSI in normal SPI mode
  // Disable SSI to allow config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]
  // Set baud rate
  mov r1, #PICO_FLASH_SPI_CLKDIV
  str r1, [r3, #SSI_BAUDR_OFFSET]
  // configure SPI mode
  ldr r1, =(CTRLR0_SPI)
  str r1, [r3, #SSI_CTRLR0_OFFSET]
  // Re-enable SSI, and select slave 0
  mov r1, #1
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // read out status register
  ldr r0, =(CMD_READ_STATUS)
  bl flash_transceive
  // check if status register is set to accept QSPI commands
  movs r1, #STATUS_QE_BITS
  tst r1, r0
  bne qspi_enabled
  
  // write enable
  ldr r0, =(CMD_WRITE_ENABLE)
  str r0, [r3, #SSI_DR0_OFFSET]
  bl wait_ssi_ready
 
  // write status and config register
  ldr r0, =(CMD_WRITE_STATUS)
  str r0, [r3, #SSI_DR0_OFFSET]
  mov r0, #STATUS_QE_BITS
  str r0, [r3, #SSI_DR0_OFFSET]
  mov r0, #0
  str r0, [r3, #SSI_DR0_OFFSET]
  bl wait_ssi_ready

qspi_enabled:
  // Disable SSI to allow further config
  mov r1, #0
  str r1, [r3, #SSI_SSIENR_OFFSET]

  // Set baud rate
  mov r1, #PICO_FLASH_SPI_CLKDIV
  str r1, [r3, #SSI_BAUDR_OFFSET]

  // configure XIP mode
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
  // load stack pointer and entry from vector table into R0,R1
  ldmia r0, {r0, r1}  
  msr msp, r0         // load main stack pointer with reset vector value
  bx r1               // jump to entry point

// Pull in common routines
#include <RP2040_boot2_common.S>

.global literals
literals:
.ltorg

.end