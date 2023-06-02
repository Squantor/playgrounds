/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series SWM functions
 */
#ifndef LPC81X_SWM_HPP
#define LPC81X_SWM_HPP

namespace instances {
namespace swm {
using namespace registers::swm;
template <uint32_t base>
struct swm {
  /**
   * @brief get registers from peripheral
   *
   * @return return pointer to registers
   */
  static registers::swm::registers *regs() {
    return reinterpret_cast<registers::swm::registers *>(base);
  }

  template <typename PIN, typename FUNC>
  constexpr void setup(PIN &pin, FUNC &function) {
    if constexpr (function.type == registers::swm::pinFunctionTypes::MOVABLE) {
      // create a mask for resetting the pin setting
      constexpr uint32_t mask = ~(0xFF << function.shift);
      regs()->PINASSIGN[function.index] = (regs()->PINASSIGN[function.index] & mask) | (pin.swmValue << function.shift);
    }
  }
};
}  // namespace swm
}  // namespace instances
#endif