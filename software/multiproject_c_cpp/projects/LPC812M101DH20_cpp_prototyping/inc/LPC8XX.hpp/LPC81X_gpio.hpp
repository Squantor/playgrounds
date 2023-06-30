/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series GPIO functions
 */
#ifndef LPC81X_GPIO_HPP
#define LPC81X_GPIO_HPP

namespace instances {
namespace gpio {
using namespace registers::gpio;
template <uint32_t base>
struct gpio {
  /**
   * @brief get registers from peripheral
   *
   * @return return pointer to gpio registers
   */
  static auto regs() {
    return reinterpret_cast<registers::gpio::registers *>(base);
  }
  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   */
  template <typename PIN>
  void high(PIN &pin) {
    regs()->B[pin.gpioPortIndex][pin.gpioPinIndex] = 0x01;
  }
  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   */
  template <typename PIN>
  void low(PIN &pin) {
    regs()->B[pin.gpioPortIndex][pin.gpioPinIndex] = 0x00;
  }
  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   * @return uint32_t
   */
  template <typename PIN>
  uint32_t get(PIN &pin) {
    return static_cast<uint32_t>(regs()->B[pin.gpioPortIndex][pin.gpioPinIndex]);
  }

  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   */
  template <typename PIN>
  void setOutput(PIN &pin) {
    regs()->DIR[pin.gpioPortIndex] = regs()->DIR[pin.gpioPortIndex] | (1 << pin.gpioPinIndex);
  }
};
}  // namespace gpio
}  // namespace instances

#endif