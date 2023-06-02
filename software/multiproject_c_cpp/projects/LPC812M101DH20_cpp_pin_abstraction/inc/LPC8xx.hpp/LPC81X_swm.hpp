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
    if constexpr (FUNC::type == registers::swm::pinFunctionTypes::MOVABLE) {
      // create a mask for resetting the pin setting
      constexpr uint32_t mask = ~(0xFF << function.shift);
      regs()->PINASSIGN[function.index] = (regs()->PINASSIGN[function.index] & mask) | (pin.pio << function.shift);
    }
    if constexpr (FUNC::type == registers::swm::pinFunctionTypes::FIXED) {
      static_assert(PIN::pio == FUNC::pio, "this fixed function is not available on this pin!");
      regs()->PINENABLE0 = regs()->PINENABLE0 & ~function.mask;
    }
  }

  constexpr void enableFixedPins(uint32_t pinMask) {
    // clearing bits enables fixed functions
    regs()->PINENABLE0 = regs()->PINENABLE0 & ~pinMask;
  }

  constexpr void disableFixedPins(uint32_t pinMask) {
    // setting bits disables fixed functions
    regs()->PINENABLE0 = regs()->PINENABLE0 | pinMask;
  }
};
}  // namespace swm
}  // namespace instances
#endif