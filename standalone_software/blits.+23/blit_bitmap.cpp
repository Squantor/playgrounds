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
#include <cstdint>
#include <cmath>
#include <span>
#include <utility>
#include "blits.hpp"
#include "bitmap.hpp"

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Blit_ops op) {
  if (dst_y > dst.get_height() || dst_x > dst.get_width()) {
    return;
  }
  // clamp bit count depending on destination bitmap size
  std::size_t src_width_bit_count{0};
  if (dst_x + src.get_width() > dst.get_width()) {
    src_width_bit_count = static_cast<std::size_t>(dst.get_width() - dst_x) * static_cast<std::size_t>(src.get_bits_per_pixel());
  } else {
    src_width_bit_count = static_cast<std::size_t>(src.get_width()) * static_cast<std::size_t>(src.get_bits_per_pixel());
  }

  std::size_t src_span_size{(static_cast<std::size_t>(src.get_width()) * static_cast<std::size_t>(src.get_height()) *
                             static_cast<std::size_t>(src.get_bits_per_pixel())) /
                            32};
  std::size_t dst_span_size{(static_cast<std::size_t>(dst.get_width()) * static_cast<std::size_t>(dst.get_height()) *
                             static_cast<std::size_t>(dst.get_bits_per_pixel())) /
                            32};
  std::span src_span(src.data(), src_span_size);
  std::span dst_span(dst.data(), dst_span_size);
  std::size_t src_bit_stride{static_cast<std::size_t>(src.get_width()) * static_cast<std::size_t>(src.get_bits_per_pixel())};
  std::size_t dst_bit_stride{static_cast<std::size_t>(dst.get_width()) * static_cast<std::size_t>(dst.get_bits_per_pixel())};
  std::size_t src_bit_size{src_span_size * 32};
  std::size_t src_bit_index{0};
  std::size_t dst_bit_index{static_cast<std::size_t>(dst_y * dst.get_width() + dst_x) *
                            static_cast<std::size_t>(dst.get_bits_per_pixel())};
  while (src_bit_index < src_bit_size) {
    blit_1d_bits(dst_span, src_span, dst_bit_index, src_bit_index, src_width_bit_count, op);
    src_bit_index += src_bit_stride;
    dst_bit_index += dst_bit_stride;
    //! @todo change source bit size to match destination to get this check out of the loop
    if (dst_bit_index > dst_span_size * 32) {
      break;
    }
  }
}

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Bitmap_coord src_x, Bitmap_coord src_y,
                 Bitmap_size width, Bitmap_size height, Blit_ops op) {
  (void)dst;
  (void)src;
  (void)dst_x;
  (void)dst_y;
  (void)src_x;
  (void)src_y;
  (void)width;
  (void)height;
  (void)op;
}