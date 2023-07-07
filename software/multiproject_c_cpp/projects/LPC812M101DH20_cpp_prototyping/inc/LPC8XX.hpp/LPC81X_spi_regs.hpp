/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series SPI register interface
 */
#ifndef LPC81X_SPI_REGS_HPP
#define LPC81X_SPI_REGS_HPP

namespace registers {
namespace spi {

/**
 * @brief SPI register definitions
 *
 */
struct registers {
  volatile uint32_t CFG;           /**< SPI Configuration register */
  volatile uint32_t DLY;           /**< SPI Delay register */
  volatile uint32_t STAT;          /**< SPI Status register */
  volatile uint32_t INTENSET;      /**< SPI Interrupt Enable Set register */
  volatile uint32_t INTENCLR;      /**< SPI Interrupt Enable Clear register */
  volatile const uint32_t RXDAT;   /**< SPI Receive Data register */
  volatile uint32_t TXDATCTL;      /**< SPI Transmit Data with Control register */
  volatile uint32_t TXDAT;         /**< SPI Transmit Data register */
  volatile uint32_t TXCRL;         /**< SPI Transmit Control register */
  volatile uint32_t DIV;           /**< SPI clock Divider register */
  volatile const uint32_t INTSTAT; /**< SPI Interrupt Status register */
};

}  // namespace spi
}  // namespace registers

#endif