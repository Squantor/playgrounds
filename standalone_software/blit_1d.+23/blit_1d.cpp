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

namespace detail {
void shift_bits(std::uint32_t &mask, std::int32_t src_shift) {
  if (src_shift > 0) {
    mask <<= src_shift;
  } else if (src_shift < 0) {
    mask >>= -src_shift;
  }
}
}  // namespace detail

void blit_op(std::uint32_t &dst, std::uint32_t src, std::int32_t src_shift, Blit_ops op) {
  std::uint32_t mask = 0xFFFFFFFF;
  detail::shift_bits(mask, src_shift);
  detail::shift_bits(src, src_shift);
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

void blit_1d_bits(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit_offset, size_t dst_bit_offset,
                  size_t bit_count, Blit_ops op) {
  std::uint32_t mask = 0xFFFFFFFF;
  // compute indices
  std::size_t src_index = src_bit_offset / 32;
  std::size_t dst_index = dst_bit_offset / 32;
  std::size_t src_end_index = (src_bit_offset + bit_count) / 32;
  std::size_t dst_end_index = (dst_bit_offset + bit_count) / 32;
  // leading bits
  // compute shift offset from src to dest
  std::size_t bit_offset = (src_bit_offset % 32) - (dst_bit_offset % 32);

  // loop
  // trailing bits
}

void blit_1d_pixels(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
                    std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op) {
  blit_1d_bits(dst, src, pixel_src * pixel_bits, pixel_dst * pixel_bits, pixel_width * pixel_bits, op);
}