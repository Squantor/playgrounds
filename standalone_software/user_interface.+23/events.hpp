/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file events.hpp
 * @brief Event definitions
 *
 */
#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstdint>

/** @brief Possible events
 */
enum class Events : std::uint8_t {
  None,      /*!< No event */
  Button,    /*!< Button event */
  PowerDown, /*!< Power down event */
  FatalError /*!< Fatal error event */
};

enum class Button : std::uint8_t {
  MenuEnterPress, /*!< Menu enter button */
  MenuLeftPress,  /*!< Menu left button pressed */
  MenuRightPress, /*!< Menu right button pressed */
};

enum class PowerDown : std::uint8_t {
  Off, /*!< Power is removed */
  User /*!< Power button is pressed */
};

enum class Error : std::uint8_t {
  Memory, /*!< Memory error */
  Device, /*!< Device error */
  Other   /*!< Other error */
};

struct EventData {
  Events event;
  union {
    Button button;
    PowerDown power_down;
    Error error;
  };
};

#endif