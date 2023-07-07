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
};
}  // namespace spi
}  // namespace instances

#endif