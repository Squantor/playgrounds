/*
SPDX-License-Identifier: MIT

Copyright (c) 2026 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file bitmap.cpp
 * \brief Class definitions for bitmap class
 */
#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <cstdint>
#include <type_traits>

namespace detail {}

using Bitmap_coord = std::uint16_t; /*!< Bitmap coordinate type */
using Bitmap_size = std::uint16_t;  /*!< Bitmap size type */
using Bitmap_bbp = std::uint8_t;    /*!< Bitmap bits per pixel type */

/**
 * @brief Class for representing a bitmap
 * @todo Change the data to a std::span
 * @tparam T
 */
template <typename T>
class Bitmap_view {
 public:
  using Pixel_type = T;
  constexpr Bitmap_view(Pixel_type *bitmap_data, Bitmap_size bitmap_width, Bitmap_size bitmap_height,
                        Bitmap_bbp bitmap_bits_per_pixel)
    : data_bitmap(bitmap_data), width(bitmap_width), height(bitmap_height), bits_per_pixel(bitmap_bits_per_pixel) {}

  [[nodiscard]] constexpr Bitmap_size get_width() const {
    return width;
  }
  [[nodiscard]] constexpr Bitmap_size get_height() const {
    return height;
  }
  [[nodiscard]] constexpr Bitmap_bbp get_bits_per_pixel() const {
    return bits_per_pixel;
  }
  [[nodiscard]] constexpr Pixel_type *data() const {
    return data_bitmap;
  }

  constexpr void fill(Pixel_type pixel)
  requires(!std::is_const_v<Pixel_type>)
  {
    Pixel_type fill_value = pixel;
    const std::size_t fill_count = get_bits_per_pixel_type() / bits_per_pixel;
    for (std::size_t count = 0; count < fill_count; count++) {
      fill_value = fill_value | static_cast<Pixel_type>(fill_value << bits_per_pixel);
    }
    const std::size_t max_bitmap_index = (width * height * bits_per_pixel) / get_bits_per_pixel_type();
    for (std::size_t i = 0; i < max_bitmap_index; i++) {
      data_bitmap[i] = fill_value;
    }
  }

  [[nodiscard]] constexpr Bitmap_view<const T> as_const() const {
    return Bitmap_view<const T>{data_bitmap, width, height, bits_per_pixel};
  }

  [[nodiscard]] constexpr Pixel_type get_pixel(Bitmap_coord x, Bitmap_coord y) const {
    if (x >= width || y >= height)
      return 0;
    using Pixel_type_nonconst = std::remove_const_t<Pixel_type>;
    const std::size_t pixel_index = (y * width) + x;
    const std::size_t bit_index = pixel_index * bits_per_pixel;
    const std::size_t data_index = bit_index / get_bits_per_pixel_type();
    const std::size_t lsb_shift = bit_index % get_bits_per_pixel_type();
    const std::size_t msb_shift = (get_bits_per_pixel_type() - lsb_shift) - bits_per_pixel;
    Pixel_type_nonconst mask = ~0;
    mask = static_cast<Pixel_type_nonconst>(mask >> msb_shift);
    const Pixel_type_nonconst pixel = static_cast<Pixel_type_nonconst>((data_bitmap[data_index] & mask) >> lsb_shift);
    return pixel;
  }

  constexpr void set_pixel(Bitmap_coord x, Bitmap_coord y, Pixel_type pixel)
  requires(!std::is_const_v<Pixel_type>)
  {
    if (x >= width || y >= height)
      return;
    const std::size_t pixel_index = (y * width) + x;
    const std::size_t bit_index = pixel_index * bits_per_pixel;
    const std::size_t data_index = bit_index / get_bits_per_pixel_type();
    const std::size_t lsb_shift = bit_index % get_bits_per_pixel_type();
    const std::size_t msb_shift = (get_bits_per_pixel_type() - lsb_shift) - bits_per_pixel;
    Pixel_type mask = ~0;
    mask = static_cast<Pixel_type>(mask >> msb_shift << lsb_shift);
    data_bitmap[data_index] = static_cast<Pixel_type>((data_bitmap[data_index] & ~mask) | (pixel << lsb_shift));
  }

 private:
  [[nodiscard]] constexpr std::size_t get_bits_per_pixel_type() const {
    return (sizeof(Pixel_type) * 8);
  }
  Pixel_type *data_bitmap;
  Bitmap_size width;
  Bitmap_size height;
  Bitmap_bbp bits_per_pixel;
};

using Bitmap = Bitmap_view<std::uint32_t>;
using Const_bitmap = Bitmap_view<const std::uint32_t>;

#endif  // BITMAP_HPP