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
enum pins {
  PIO0_00,
  PIO0_01,
  PIO0_02,
  PIO0_03,
  PIO0_04,
  PIO0_05,
  PIO0_06,
  PIO0_07,
  PIO0_08,
  PIO0_09,
  PIO0_10,
  PIO0_11,
  PIO0_12,
  PIO0_13,
  PIO0_14,
  PIO0_15,
  PIO0_16,
  PIO0_17,
};

template <pins p>
struct pin {};

// iocon pin specializations
template <>
struct pin<pins::PIO0_00> {
  static constexpr size_t ioconIndex = 17;
};
template <>
struct pin<pins::PIO0_01> {
  static constexpr size_t ioconIndex = 11;
};
template <>
struct pin<pins::PIO0_02> {
  static constexpr size_t ioconIndex = 6;
};
template <>
struct pin<pins::PIO0_03> {
  static constexpr size_t ioconIndex = 5;
};
template <>
struct pin<pins::PIO0_04> {
  static constexpr size_t ioconIndex = 4;
};
template <>
struct pin<pins::PIO0_05> {
  static constexpr size_t ioconIndex = 3;
};

// specializations work in this case with structs and configuring them at compiletime
// you just instantiate one setup struct and feed it at runtime to the iocon configurator
// iocon is just a class that will setup a pin (from the specialization tree) with the proper settings
// this iocon should be folded in some kind of pin properties,

}  // namespace iocon
}  // namespace instances

#endif