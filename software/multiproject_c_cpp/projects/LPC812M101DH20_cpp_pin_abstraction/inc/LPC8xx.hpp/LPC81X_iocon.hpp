/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series IOCON functions
 */
#ifndef LPC81X_IOCON_HPP
#define LPC81X_IOCON_HPP

namespace instances {
namespace iocon {
using namespace registers::iocon;
template <uint32_t base>
struct iocon {
  /**
   * @brief get registers from peripheral
   *
   * @return return pointer to iocon registers
   */
  static auto regs() {
    return reinterpret_cast<registers::iocon::registers *>(base);
  }
  /**
   * @brief Setup normal IOCON pin
   *
   * @tparam T
   * @param pin
   * @param mode
   * @param filter
   * @param clock
   * @param options
   */
  template <typename T>
  void setup(T &pin, pullModes mode, pinFiltering filter, clockDivider clock, uint32_t options) {
    regs()->PIO[pin.ioconIndex] = mode | filter | clock | options;
  }
  template <typename T>
  void setup(T &pin, pullModes mode, uint32_t options) {
    regs()->PIO[pin.ioconIndex] = mode | options;
  }
  template <typename T>
  void setup(T &pin, pullModes mode) {
    regs()->PIO[pin.ioconIndex] = mode;
  }
};
}  // namespace iocon
}  // namespace instances

#endif