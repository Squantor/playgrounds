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
    mask = mask << src_shift;
  } else if (src_shift < 0) {
    mask = mask >> -src_shift;
  }
}
}  // namespace detail

void blit_op(std::uint32_t &dst, std::uint32_t src, std::uint32_t mask, Blit_ops op) {
  switch (op) {
    case Blit_ops::COPY:
      dst = ((dst & ~mask) | ((src)&mask));
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

// Todo: implement memmove semantics
// this is a variant of blit that focuses on destination indices and bit count subtraction
void blit_1d_bits(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit, size_t bit_width,
                  Blit_ops op) {
  (void)dst;
  (void)src;
  (void)src_bit;
  (void)dst_bit;
  (void)bit_width;
  (void)op;
  // 32 bit shift factor between source and destination
  std::int32_t shift = static_cast<std::int32_t>(dst_bit % 32) - static_cast<std::int32_t>(src_bit % 32);
  std::size_t dst_bit_index = dst_bit;
  std::size_t src_bit_index = src_bit;
  std::size_t bit_count = bit_width;
  std::uint32_t bits;
  std::uint32_t mask;
  // heading bits handling
  std::size_t dst_bit_header = dst_bit % 32;
  if (dst_bit_header != 0) {
    bits = src[src_bit_index / 32];
    detail::shift_bits(bits, shift);
    mask = 0xFFFFFFFF << dst_bit_header;
    blit_op(dst[dst_bit_index / 32], bits, mask, op);
    dst_bit_index += (32 - dst_bit_header);
    src_bit_index += (32 - dst_bit_header);
    bit_count -= (32 - dst_bit_header);
  }
  // loop
  std::size_t src_bit_step = src_bit_index % 32;
  while (bit_count > 31) {
    // handling of 32 bit sized chunks
    if (shift == 0) {
      bits = src[src_bit_index / 32];
      src_bit_index = src_bit_index + 32;
    } else {
      bits = src[src_bit_index / 32] >> (src_bit_step);
      src_bit_index = src_bit_index + (src_bit_step);
      src_bit_step = 32 - src_bit_step;
      bits = bits | src[src_bit_index / 32] << (src_bit_step);
      src_bit_index = src_bit_index + (32 - src_bit_step);
    }
    blit_op(dst[dst_bit_index / 32], bits, 0xFFFFFFFF, op);
    bit_count -= 32;
    dst_bit_index += 32;
  }
  // trailing bits handling
  if (bit_count > 0) {
    bits = src[src_bit_index / 32];
    bits = bits >> (src_bit_index % 32);
    std::size_t trailing_overflow = (src_bit_index + bit_count) % 32;
    // handling for trailing overflow
    if (trailing_overflow != 0) {
      // TODO: handle last bit of bits
    }
    mask = 0xFFFFFFFF >> (32 - bit_count);
    blit_op(dst[dst_bit_index / 32], bits, mask, op);
  }
}

// Todo: implement memmove semantics
// this is a variant of blit that focuses on destination indices and bit count subtraction
void blit_1d_bits_old001(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit,
                         size_t bit_width, Blit_ops op) {
  (void)dst;
  (void)src;
  (void)src_bit;
  (void)dst_bit;
  (void)bit_width;
  (void)op;
  std::size_t dst_bit_index = dst_bit;
  std::size_t src_bit_index = src_bit;
  std::size_t dst_header_bits = dst_bit_index % 32;
  std::size_t src_header_bits = src_bit_index % 32;
  std::int32_t shift = static_cast<std::int32_t>(dst_header_bits) - static_cast<std::int32_t>(src_header_bits);
  std::uint32_t bits;
  std::size_t bit_count = bit_width;
  // heading bits
  // todo: handling dissimilar dst/src shifts
  if (dst_header_bits > 0 || src_header_bits > 0) {
    std::uint32_t src_mask = 0xFFFFFFFF << src_header_bits;
    std::uint32_t dst_mask = 0xFFFFFFFF << dst_header_bits;
    bits = src[src_bit_index / 32] & src_mask;
    detail::shift_bits(bits, shift);
    blit_op(dst[dst_bit_index / 32], bits, dst_mask, op);
    bit_count -= dst_header_bits;
    dst_bit_index += dst_header_bits;
    src_bit_index += dst_header_bits;
  }
  // loop
  while (bit_count > 31) {
    // handling of 32 bit sized chunks
    bits = src[src_bit_index / 32];
    blit_op(dst[dst_bit_index / 32], bits, 0xFFFFFFFF, op);
    bit_count -= 32;
    dst_bit_index += 32;
    src_bit_index += 32;
  }
  if (bit_count > 0) {
    std::uint32_t src_mask = 0xFFFFFFFF >> (32 - src_header_bits);
    std::uint32_t dst_mask = 0xFFFFFFFF >> (32 - dst_header_bits);
    bits = src[src_bit_index / 32] & src_mask;
    detail::shift_bits(bits, shift);
    blit_op(dst[dst_bit_index / 32], bits, dst_mask, op);
    bit_count -= dst_header_bits;
    dst_bit_index += dst_header_bits;
    src_bit_index += dst_header_bits;
  }
}

// Todo: implement memmove semantics
// older version, got overwhelmed by all the index calculations, taking a step back
void blit_1d_bits_old000(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit,
                         size_t bit_width, Blit_ops op) {
  std::uint32_t mask;
  std::uint32_t bits;
  // compute indices
  std::size_t src_index = src_bit / 32;
  std::size_t dst_index = dst_bit / 32;
  std::int32_t src_dst_bit_shift = (dst_bit % 32) - (src_bit % 32);
  // std::size_t src_end_index = (src_bit + bit_width) / 32;
  // std::size_t dst_end_index = (dst_bit + bit_width) / 32;
  //  leading bits
  //  compute lead source mask
  mask = 0xFFFFFFFF << (src_bit % 32);
  // fetch data
  bits = src[src_index] & mask;
  detail::shift_bits(bits, src_dst_bit_shift);
  // compute destination mask
  mask = 0xFFFFFFFF << (dst_bit % 32);
  // execute operation leading bits operation
  blit_op(dst[dst_index], bits, mask, op);
  bit_width = bit_width - (32 - (dst_bit % 32));
  // loop
  // create source mask that will be used in the loop
  mask = 0xFFFFFFFF;
  detail::shift_bits(mask, src_dst_bit_shift);
  src_index++;
  dst_index++;
  while (bit_width >= 32) {
    // assemble destination word
    bits = src[src_index] & mask;
    src_index++;
    // write data to destination
    blit_op(dst[dst_index], bits, 0xFFFFFFFF, op);
    // update indices
    bit_width -= 32;
    dst_index++;
  }
  // Do we have any trailing bits?
  if (bit_width == 0)
    return;
  // compute trailing source mask
  mask = 0xFFFFFFFF >> (32 - bit_width);
  // fetch trailing bits
  bits = src[src_index] & mask;
  // offset to source
  detail::shift_bits(bits, src_dst_bit_shift);
  detail::shift_bits(mask, src_dst_bit_shift);
  // execute trailing bits operation
  blit_op(dst[dst_index], bits, mask, op);
}

void blit_1d_pixels(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, std::size_t pixel_bits, std::size_t pixel_width,
                    std::size_t pixel_dst, std::size_t pixel_src, Blit_ops op) {
  blit_1d_bits(dst, src, pixel_src * pixel_bits, pixel_dst * pixel_bits, pixel_width * pixel_bits, op);
}