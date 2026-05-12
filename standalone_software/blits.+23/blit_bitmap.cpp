/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_bitmap.hpp
 * @brief bitmap blit functions
 * @version 20260430
 *
 */

#include <cstddef>
#include <cmath>
#include <span>
#include "blits.hpp"
#include "bitmap.hpp"

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Blit_ops op) {
  blit_bitmap(dst, src, dst_x, dst_y, 0, 0, src.get_width(), src.get_height(), op);
}

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Bitmap_coord src_x, Bitmap_coord src_y,
                 Bitmap_size src_width, Bitmap_size src_height, Blit_ops op) {
  if (dst_y > dst.get_height() || dst_x > dst.get_width()) {
    return;
  }
  // clamp bit counts depending on bitmap sizes
  if (src_x + src_width > src.get_width()) {
    src_width = src.get_width() - src_x;
  }
  std::size_t src_width_bit_count{0};
  if (dst_x + src_width > dst.get_width()) {
    src_width_bit_count = static_cast<std::size_t>(dst.get_width() - dst_x) * static_cast<std::size_t>(src.get_bits_per_pixel());
  } else {
    src_width_bit_count = static_cast<std::size_t>(src_width) * static_cast<std::size_t>(src.get_bits_per_pixel());
  }
  // prepare bounds/sizes
  const std::size_t src_span_size{(static_cast<std::size_t>(src.get_width()) * static_cast<std::size_t>(src.get_height()) *
                                   static_cast<std::size_t>(src.get_bits_per_pixel())) /
                                  32};
  const std::size_t dst_span_size{(static_cast<std::size_t>(dst.get_width()) * static_cast<std::size_t>(dst.get_height()) *
                                   static_cast<std::size_t>(dst.get_bits_per_pixel())) /
                                  32};
  const std::span src_span(src.data(), src_span_size);
  const std::span dst_span(dst.data(), dst_span_size);
  const std::size_t src_bit_stride{static_cast<std::size_t>(src.get_width()) * static_cast<std::size_t>(src.get_bits_per_pixel())};
  const std::size_t dst_bit_stride{static_cast<std::size_t>(dst.get_width()) * static_cast<std::size_t>(dst.get_bits_per_pixel())};
  const std::size_t src_bit_end{((src_y + src_height) * src.get_width() + src_x) *
                                static_cast<std::size_t>(src.get_bits_per_pixel())};
  std::size_t src_bit_index{(src_y * src.get_width() + src_x) * static_cast<std::size_t>(src.get_bits_per_pixel())};
  std::size_t dst_bit_index{static_cast<std::size_t>(dst_y * dst.get_width() + dst_x) *
                            static_cast<std::size_t>(dst.get_bits_per_pixel())};
  while (src_bit_index < src_bit_end) {
    blit_1d_bits(dst_span, src_span, dst_bit_index, src_bit_index, src_width_bit_count, op);
    src_bit_index += src_bit_stride;
    dst_bit_index += dst_bit_stride;
    //! @todo adjust src_bit_end to match destination to get this check out of the loop
    if (dst_bit_index > dst_span_size * 32) {
      break;
    }
  }
}