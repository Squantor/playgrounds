/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file display.hpp
 * @brief Display interface class definition
 *
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>

struct Display {
  virtual void print(const char *) = 0;
  virtual void flip() = 0;
  virtual std::uint16_t get_x_size() = 0;
  virtual std::uint16_t get_y_size() = 0;
};

#endif