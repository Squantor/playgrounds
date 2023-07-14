/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series SPI functions
 */
#ifndef LPC81X_SPI_HPP
#define LPC81X_SPI_HPP

namespace instances {
namespace spi {
using namespace registers::spi;
template <uint32_t base>
struct spi {
  /**
   * @brief get registers from peripheral
   *
   * @return return pointer to spi registers
   */
  static auto regs() {
    return reinterpret_cast<registers::spi::registers *>(base);
  }

  /**
   * @brief Initialise SPI peripheral as master device
   *
   * Make sure clocks are enabled to the SPI peripheral first before calling this method!
   *
   * @param bitRate requested bit rate
   * @return actual bit rate
   */
  uint32_t initMaster(uint32_t bitRate) {
    uint32_t actualBitRate = setBitRate(bitRate);
    regs()->CFG = CFG::ENABLE | CFG::MASTER;
    return actualBitRate;
  }

  /**
   * @brief Set the SPI peripheral bit rate
   *
   * Uses defined CLOCK_AHB to compute the actual bit rate
   *
   * @param bitRate requested bit rate
   * @return actual bit rate
   */
  uint32_t setBitRate(uint32_t bitRate) {
    // compute divider and truncate so we can observe a possible round off
    uint16_t divider = static_cast<uint16_t>(CLOCK_AHB / bitRate);
    regs()->DIV = DIV::DIVVAL(divider);
    return CLOCK_AHB / divider;
  }
};
}  // namespace spi
}  // namespace instances

#endif