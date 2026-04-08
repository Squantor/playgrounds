/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d.hpp
 * @brief 1D blit functions
 * @version 20260403
 *
 */
#include "blit_1d.hpp"

void blit_op(std::uint32_t &dst, std::uint32_t src, std::int32_t src_shift, Blit_ops op) {
  std::uint32_t mask = 0xFFFFFFFF;
  if (src_shift > 0) {
    mask <<= src_shift;
    src <<= src_shift;
  } else if (src_shift < 0) {
    mask >>= -src_shift;
    src >>= -src_shift;
  }
  mask = ~mask;

  switch (op) {
    case Blit_ops::COPY:
      dst = ((dst & mask) | src);
      break;
    case Blit_ops::INVERT:
      dst = ~((dst & mask) | src);
      break;
    case Blit_ops::AND:
      dst &= ((dst & mask) | src);
      break;
    case Blit_ops::OR:
      dst |= ((dst & mask) | src);
      break;
    case Blit_ops::XOR:
      dst ^= ((dst & mask) | src);
      break;
    default:
      break;
  }
}

void blit_1d(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
             std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op) {
  // compute indices, assume 32 bit elements
  std::size_t src_index = (pixel_src * pixel_bits) >> 5;
  std::size_t dst_index = (pixel_dst * pixel_bits) >> 5;
  std::size_t src_end_index = (((pixel_src + pixel_width) * pixel_bits) >> 5);
  std::size_t dst_end_index = (((pixel_dst + pixel_width) * pixel_bits) >> 5);
  std::size_t src_bit_offset = (pixel_src * pixel_bits) & 0x1F;
  std::size_t dst_bit_offset = (pixel_dst * pixel_bits) & 0x1F;
  // compute masks
  std::uint32_t src_mask = 0xFFFFFFFF << src_bit_offset;
  std::uint32_t dst_mask = 0xFFFFFFFF << dst_bit_offset;
  std::uint32_t pixels;  // Working buffer
  // First element start
  pixels = src[src_index] & src_mask;
  // Loop
  // Do not invert source mask if offset is zero
  // do not invert destination mask if offset is zero
  // Last element start
}