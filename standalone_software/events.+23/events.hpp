/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file events.hpp
 * Event handler definitions
 */
#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstdint>

/** @brief Possible events
 */
enum class Events : uint8_t {
   None,      /*!< No event */
   Button,    /*!< Button event */
   PowerDown, /*!< Power down event */
   FatalError /*!< Fatal error event */
};

enum class Button : uint8_t {
   Up,  /*< Button up */
   Down /*< Button down */
};

enum class PowerDown : uint8_t {
   Off, /*!< Power is removed */
   User /*!< Power button is pressed */
};

enum class Error : uint8_t {
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