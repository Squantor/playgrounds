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
/**
 * @brief shift bits either positive or negative
 * @param mask mask to shift
 * @param src_shift shift amount/count
 */
void shift_bits(std::uint32_t &mask, std::int32_t src_shift) {
  if (src_shift > 0) {
    mask <<= src_shift;
  } else if (src_shift < 0) {
    mask >>= -src_shift;
  }
}
}  // namespace detail

void blit_op(std::uint32_t &dst, std::uint32_t src, std::uint32_t mask, Blit_ops op) {
  
  switch (op) {
    case Blit_ops::COPY:
      dst = ((dst & ~mask) | ((src) & mask));
      break;
    case Blit_ops::INVERT:
      dst = ((dst & ~mask) | ((~src) & mask));
      break;
    case Blit_ops::AND:
      dst = ((dst & ~mask) | ((src & dst) & mask));
      break;
    case Blit_ops::OR:
      dst = ((dst & ~mask) | ((src | dst) & mask));
      break;
    case Blit_ops::XOR:
      dst = ((dst & ~mask) | ((src ^ dst) & mask));
      break;
    default:
      break;
  }
}

void blit_1d_bits(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit_offset, size_t dst_bit_offset,
                  size_t bit_count, Blit_ops op) {
  (void) bit_count;
  (void) op;
  std::uint32_t mask;
  std::uint32_t bits;
  // compute indices
  std::size_t src_index = src_bit_offset / 32;
  std::size_t dst_index = dst_bit_offset / 32;
  std::int32_t bit_shift = (src_bit_offset % 32) - (dst_bit_offset % 32);
  //std::size_t src_end_index = (src_bit_offset + bit_count) / 32;
  //std::size_t dst_end_index = (dst_bit_offset + bit_count) / 32;
  // leading bits
  // compute lead source mask
  mask = 0xFFFFFFFF << (src_bit_offset % 32);
  // fetch data
  bits = src[src_index] & mask;
  detail::shift_bits(bits, bit_shift);
  // compute destination mask
  mask = 0xFFFFFFFF << (dst_bit_offset % 32);
  // execute operation leading bits operation
  dst[dst_index] = ((dst[dst_index] & ~mask) | (bits & mask));
  // loop
  // trailing bits
}

void blit_1d_pixels(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
                    std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op) {
  blit_1d_bits(dst, src, pixel_src * pixel_bits, pixel_dst * pixel_bits, pixel_width * pixel_bits, op);
}