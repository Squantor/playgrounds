/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC812M101DH20 pin definitions
 */

#include <cstddef>

#ifndef LPC812M101DH20_PINS_HPP
#define LPC812M101DH20_PINS_HPP

namespace instances {
namespace iocon {

/**
 * @brief base template
 *
 * @tparam p pin to specialize in configure
 */
template <IOpins p>
struct pin {};

/**
 * @brief PIO0_00 specialisation
 *
 * @tparam
 */
template <>
struct pin<IOpins::PIO0_00> {
  static constexpr uint8_t ioconIndex = 17;
};
template <>
struct pin<IOpins::PIO0_01> {
  static constexpr uint8_t ioconIndex = 11;
};
template <>
struct pin<IOpins::PIO0_02> {
  static constexpr uint8_t ioconIndex = 6;
};
template <>
struct pin<IOpins::PIO0_03> {
  static constexpr uint8_t ioconIndex = 5;
};
template <>
struct pin<IOpins::PIO0_04> {
  static constexpr uint8_t ioconIndex = 4;
};
template <>
struct pin<IOpins::PIO0_05> {
  static constexpr uint8_t ioconIndex = 3;
};
template <>
struct pin<IOpins::PIO0_06> {
  static constexpr uint8_t ioconIndex = 16;
};
template <>
struct pin<IOpins::PIO0_07> {
  static constexpr uint8_t ioconIndex = 15;
};
template <>
struct pin<IOpins::PIO0_08> {
  static constexpr uint8_t ioconIndex = 14;
};
template <>
struct pin<IOpins::PIO0_09> {
  static constexpr uint8_t ioconIndex = 13;
};
template <>
struct pin<IOpins::PIO0_10> {
  static constexpr uint8_t ioconIndex = 8;
  static constexpr uint8_t isI2Cpin = 1;
};
template <>
struct pin<IOpins::PIO0_11> {
  static constexpr uint8_t ioconIndex = 7;
  static constexpr uint8_t isI2Cpin = 1;
};
template <>
struct pin<IOpins::PIO0_12> {
  static constexpr uint8_t ioconIndex = 2;
};
template <>
struct pin<IOpins::PIO0_13> {
  static constexpr uint8_t ioconIndex = 1;
};
template <>
struct pin<IOpins::PIO0_14> {
  static constexpr uint8_t ioconIndex = 12;
};
template <>
struct pin<IOpins::PIO0_15> {
  static constexpr uint8_t ioconIndex = 10;
};
template <>
struct pin<IOpins::PIO0_16> {
  static constexpr uint8_t ioconIndex = 9;
};
template <>
struct pin<IOpins::PIO0_17> {
  static constexpr uint8_t ioconIndex = 0;
};
/* Braindump:
specializations work in this case with structs and configuring them at compiletime
you just instantiate one setup struct and feed it at runtime to the iocon configurator
iocon is just a class that will setup a pin (from the specialization tree) with the proper settings
this iocon should be folded in some kind of pin properties,
*/

}  // namespace iocon
}  // namespace instances

#endif