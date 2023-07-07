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
   */
  template <typename PIN>
  void toggle(PIN &pin) {
    regs()->B[pin.gpioPortIndex][pin.gpioPinIndex] = ~regs()->B[pin.gpioPortIndex][pin.gpioPinIndex];
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
   * @tparam PORT
   * @param port
   * @param setting
   */
  template <typename PORT>
  void portHigh(PORT &port, uint32_t setting) {
    regs()->SET[port.gpioPortIndex] = setting;
  }

  /**
   * @brief
   *
   * @tparam PORT
   * @param port
   * @param setting
   * @return voic
   */
  template <typename PORT>
  void portLow(PORT &port, uint32_t setting) {
    regs()->CLR[port.gpioPortIndex] = setting;
  }

  /**
   * @brief
   *
   * @tparam PORT
   * @param port
   * @param setting
   */
  template <typename PORT>
  void portToggle(PORT &port, uint32_t setting) {
    regs()->NOT[port.gpioPortIndex] = setting;
  }

  /**
   * @brief TODO
   *
   * @tparam PORT
   * @param port
   * @param setting
   * @param mask
   */
  template <typename PORT>
  void portSet(PORT &port, uint32_t setting, uint32_t mask) {
    regs()->DIR[port.gpioPortIndex] = (regs()->DIR[port.gpioPortIndex] & mask) | (setting & mask);
  }

  /**
   * @brief TODO
   *
   * @tparam PORT
   * @param port
   * @param setting
   */
  template <typename PORT>
  void portSet(PORT &port, uint32_t setting) {
    regs()->DIR[port.gpioPortIndex] = setting;
  }

  /**
   * @brief TODO
   *
   * @tparam PORT
   * @param port
   * @param mask
   * @return uint32_t
   */
  template <typename PORT>
  uint32_t portGet(PORT &port, uint32_t mask) {
    return static_cast<uint32_t>(regs()->PIN[port.gpioPortIndex]) & mask;
  }

  /**
   * @brief TODO
   *
   * @tparam PORT
   * @param port
   * @return uint32_t
   */
  template <typename PORT>
  uint32_t portGet(PORT &port) {
    return static_cast<uint32_t>(regs()->PIN[port.gpioPortIndex]);
  }

  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   */
  template <typename PIN>
  void output(PIN &pin) {
    regs()->DIR[pin.gpioPortIndex] = regs()->DIR[pin.gpioPortIndex] | (1 << pin.gpioPinIndex);
  }

  /**
   * @brief
   *
   * @tparam PIN
   * @param pin
   */
  template <typename PIN>
  void input(PIN &pin) {
    regs()->DIR[pin.gpioPortIndex] = regs()->DIR[pin.gpioPortIndex] & ~(1 << pin.gpioPinIndex);
  }

  /**
   * @brief
   *
   * @tparam PORT
   * @param port
   * @param setting
   * @param mask
   */
  template <typename PORT>
  void portDirection(PORT &port, uint32_t setting, uint32_t mask) {
    regs()->DIR[port.gpioPortIndex] = (regs()->DIR[port.gpioPortIndex] & ~mask) | (setting & mask);
  }

  /**
   * @brief
   *
   * @tparam PORT
   * @param port
   * @param setting
   */
  template <typename PORT>
  void portDirection(PORT &port, uint32_t setting) {
    regs()->DIR[port.gpioPortIndex] = setting;
  }
};
}  // namespace gpio
}  // namespace instances

#endif