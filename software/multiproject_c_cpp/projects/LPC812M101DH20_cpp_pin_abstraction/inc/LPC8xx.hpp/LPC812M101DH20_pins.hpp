/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC812M101DH20 pin definitions
 */

#ifndef LPC812M101DH20_PINS_HPP
#define LPC812M101DH20_PINS_HPP

namespace instances {

enum pinTypeFlags : uint8_t {
  NORMAL = 0,           /**< Normal pin without any special handling */
  IOCON_I2C = (1 << 0), /**< IOCON special handling for I2C */
};

/**
 * @brief Available pins on LPC812M101DH20
 *
 */
enum class IOpins : uint8_t {
  PIN00, /**< Pin 0 */
  PIN01, /**< Pin 1 */
  PIN02, /**< Pin 2 */
  PIN03, /**< Pin 3 */
  PIN04, /**< Pin 4 */
  PIN05, /**< Pin 5 */
  PIN06, /**< Pin 6 */
  PIN07, /**< Pin 7 */
  PIN08, /**< Pin 8 */
  PIN09, /**< Pin 9 */
  PIN10, /**< Pin 10 */
  PIN11, /**< Pin 11 */
  PIN12, /**< Pin 12 */
  PIN13, /**< Pin 13 */
  PIN14, /**< Pin 14 */
  PIN15, /**< Pin 15 */
  PIN16, /**< Pin 16 */
  PIN17, /**< Pin 17 */
};

/**
 * @brief Available ports on LPC812M101DH20
 *
 */
enum class IOports : uint8_t {
  PORT0, /**< Port 0 */
};

namespace iocon {

/**
 * @brief base template
 *
 * @tparam T_PORT IO port
 * @tparam T_PIN  IO pin
 */
template <IOports T_PORT, IOpins T_PIN, bool DUMMY = false>
struct pin {
  static_assert(DUMMY, "This configuration is invalid!");
};

/**
 * @brief PIO0_00 specialisation
 *
 * @tparam
 */
template <>
struct pin<IOports::PORT0, IOpins::PIN00> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 17;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN01> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 11;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN02> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 6;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN03> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 5;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN04> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 4;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN05> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 3;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN06> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 16;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN07> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 15;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN08> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 14;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN09> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 13;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN10> {
  static constexpr uint8_t typeFlags = pinTypeFlags::IOCON_I2C;
  static constexpr uint8_t ioconIndex = 8;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN11> {
  static constexpr uint8_t typeFlags = pinTypeFlags::IOCON_I2C;
  static constexpr uint8_t ioconIndex = 7;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN12> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 2;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN13> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 1;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN14> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 12;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN15> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 10;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN16> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 9;
};
template <>
struct pin<IOports::PORT0, IOpins::PIN17> {
  static constexpr uint8_t typeFlags = pinTypeFlags::NORMAL;
  static constexpr uint8_t ioconIndex = 0;
};
/* Braindump:
specializations work in this case with structs and configuring them at compiletime
you just instantiate one setup struct and feed it at runtime to the iocon configurator
iocon is just a class that will setup a pin (from the specialization tree) with the proper settings
this iocon should be folded in some kind of pin properties,
Another insight, you encode values in types, as each template is a unique type.
*/

}  // namespace iocon
}  // namespace instances

#endif