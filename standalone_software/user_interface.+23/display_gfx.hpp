/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file display_gfx.hpp
 * @brief Graphical display interface class definition
 *
 */
#ifndef DISPLAY_GFX_HPP
#define DISPLAY_GFX_HPP

#include <cstdint>

template <typename Pixel_type, std::uint16_t x_size, std::uint16_t y_size>
struct Display_gfx {
  virtual void putpixel(std::uint16_t x, std::uint16_t y, Pixel_type pixel) = 0;
  // line draw
  // block fill
  // blit
  virtual void fill(std::uint16_t start_x, std::uint16_t start_y, std::uint16_t end_x, std::uint16_t end_y) = 0;
  virtual void clear(void) = 0;
  virtual void print(const char *) = 0;
  /**
   * @brief Apply framebuffer to display hardware
   */
  virtual void flip(void) = 0;
};

#endif