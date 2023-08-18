/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef NUCLONE_RP2040_HPP
#define NUCLONE_RP2040_HPP

#define FREQ_XTAL (12000000u)      /**< Crystal oscillator frequncy */
#define FREQ_CPU (120000000u)      /**< CPU frequency */
#define FREQ_USB (48000000u)       /**< USB frequency */
#define FREQ_ADC (48000000u)       /**< ADC frequency */
#define FREQ_RTC (FREQ_XTAL / 256) /**< RTC frequency */
#define FREQ_PERI (FREQ_CPU)       /**< Peripherals frequency */

#include <mcu_ll.h>

#define TICKS_PER_S (8u)

void boardInit(void);

#define LED_PIN BANK0_GPIO25
#define LED_MASK BANK0_GPIO25_MASK
#define CLOCK_PIN BANK0_GPIO21
#define CLOCK_MASK BANK0_GPIO21_MASK

#define UART_TX_PIN BANK0_GPIO0
#define UART_TX_MASK BANK0_GPIO0_MASK
#define UART_RX_PIN BANK0_GPIO1
#define UART_RX_MASK BANK0_GPIO1_MASK

#define SPI_SCK_PIN BANK0_GPIO2
#define SPI_SCK_MASK BANK0_GPIO2_MASK
#define SPI_MOSI_PIN BANK0_GPIO3
#define SPI_MOSI_MASK BANK0_GPIO3_MASK
#define SPI_MISO_PIN BANK0_GPIO4
#define SPI_MISO_MASK BANK0_GPIO4_MASK
#define SPI_CS_PIN BANK0_GPIO5
#define SPI_CS_MASK BANK0_GPIO5_MASK

#define I2C_SCL_PIN BANK0_GPIO9
#define I2C_SCL_MASK BANK0_GPIO9_MASK
#define I2C_SDA_PIN BANK0_GPIO8
#define I2C_SDA_MASK BANK0_GPIO8_MASK

#endif