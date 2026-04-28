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
#include <cstddef>
#include <cstdint>
#include <cmath>
#include <span>
#include <utility>
#include "blits.hpp"

namespace detail {
/**
 * @brief shift bits either positive or negative
 * @param bits bits to shift
 * @param shift shift amount/count
 * @return shifted bits
 */
std::uint32_t shift_bits(std::uint32_t bits, std::int32_t shift) {
  if (shift > 32 || shift < -32) {
    return 0;
  }
  if (shift > 0) {
    return bits << shift;
  } else if (shift < 0) {
    return bits >> -shift;
  }
  return bits;
}

std::uint32_t get_bits(std::span<const std::uint32_t> src, std::size_t src_bit) {
  std::uint32_t bits = 0;
  const std::size_t shift = src_bit % 32;
  const std::size_t index = src_bit / 32;
  if (shift != 0) {
    bits = src[index] >> shift;
    if (index + 1 < src.size())
      bits = bits | src[index + 1] << (32 - shift);
  } else {
    bits = src[index];
  }
  return bits;
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

/**
 * @brief simple blit that copies bit by bit, used for correctness checks
 * @todo add memmove semantics
 * @note Mostly used for debugging and correctness checks, quite slow
 */
void blit_1d_bits_simple(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit,
                         size_t bit_width, Blit_ops op) {
  // setup source/destination masks
  std::uint32_t src_mask = 0x00000001 << (src_bit % 32);
  std::uint32_t dst_mask = 0x00000001 << (dst_bit % 32);
  for (size_t i = 0; i < bit_width; i++) {
    // extract one bit from source
    uint32_t bit = src[src_bit / 32] & src_mask;
    // convert bit to destination bit position
    if (bit != 0) {
      bit = dst_mask;
    } else {
      bit = 0;
    }
    // write one bit to destination with the operation in mind
    blit_op(dst[dst_bit / 32], bit, dst_mask, op);
    // shift masks
    src_mask = src_mask << 1;
    if (src_mask == 0) {
      src_mask = 0x00000001;
    }
    dst_mask = dst_mask << 1;
    if (dst_mask == 0) {
      dst_mask = 0x00000001;
    }
    src_bit++;
    dst_bit++;
  }
}

/**
 * @brief this is a variant of blit that focuses on whole destination indices and bit count subtraction
 * @note More optimized for size than raw speed, but still better then single bit reads
 * @todo reading from source can be slow, cache source element from source element+1
 */
void blit_1d_bits(std::span<std::uint32_t> dst, std::span<const std::uint32_t> src, size_t dst_bit, size_t src_bit,
                  size_t bit_width, Blit_ops op) {
  std::size_t bit_count = bit_width;
  std::uint32_t bits;
  std::uint32_t mask = 0xFFFFFFFF;
  std::size_t todo_bits = 32;
  // handle starting incomplete element
  // determine if we start with an incomplete element
  std::size_t header_offset = dst_bit % 32;
  if (header_offset != 0) {
    // setup loop to handle first incomplete element
    todo_bits = todo_bits - header_offset;
    mask = 0xFFFFFFFF << header_offset;
    // check if we have a very small span
    if (todo_bits > bit_count) {
      mask = mask & (0xFFFFFFFF >> (todo_bits - bit_count));
      todo_bits = bit_count;
    }
  }
  // handle complete elements
  while (bit_count > 0) {
    if (src_bit < header_offset) {
      // the header offset is out of bounds, fixup
      bits = src[0] << (header_offset - src_bit);
    } else {
      bits = detail::get_bits(src, src_bit - header_offset);
    }

    blit_op(dst[dst_bit / 32], bits, mask, op);

    bit_count -= todo_bits;
    src_bit += todo_bits;
    dst_bit += todo_bits;
    header_offset = 0;  // reset header offset

    if (bit_count > 31) {
      mask = 0xFFFFFFFF;
      todo_bits = 32;
    } else if (bit_count > 0) {
      // last incomplete element
      mask = 0xFFFFFFFF >> (32 - bit_count);
      todo_bits = bit_count;
    }
  }
}

/**
 * @brief this is a variant of blit that focuses on whole destination indices and bit count subtraction
 * Only writes its bitmasks!
 * @note Commented out as used during development, might come in handy when debugging
 */
/*
void blit_1d_bits_mask(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit, size_t
bit_width, Blit_ops op) { std::size_t bit_count = bit_width; std::uint32_t bits; std::uint32_t mask = 0xFFFFFFFF; std::size_t
todo_bits = 32;
  // handle starting incomplete element
  // determine if we have an incomplete element
  std::size_t header_bits = dst_bit % 32;
  if (header_bits != 0) {
    // setup loop to handle incomplete element
    todo_bits = todo_bits - header_bits;
    mask = 0xFFFFFFFF << header_bits;
    // check if we have a very small span
    if (todo_bits > bit_count) {
      mask = mask & (0xFFFFFFFF >> (todo_bits - bit_count));
      todo_bits = bit_count;
    }
  }
  // handle complete elements
  while (bit_count > 0) {
    bits = mask;
    blit_op(dst[dst_bit / 32], bits, mask, op);

    bit_count = bit_count - todo_bits;
    src_bit += todo_bits;
    dst_bit += todo_bits;

    if (bit_count > 31) {
      mask = 0xFFFFFFFF;
      todo_bits = 32;
    } else if (bit_count > 0) {
      // last incomplete element
      mask = 0xFFFFFFFF >> (32 - bit_count);
      todo_bits = bit_count;
    }
  }
}
*/

void blit_1d_pixels(std::span<std::uint32_t> dst, std::span<const std::uint32_t> src, std::size_t pixel_bits,
                    std::size_t pixel_width, std::size_t pixel_dst, std::size_t pixel_src, Blit_ops op) {
  // check for order
  if (dst.data() == src.data()) {
    if (pixel_dst > pixel_src) {
      std::swap(pixel_dst, pixel_src);
    }
  }
  // clamp pixel_width
  const std::size_t dst_pixel_width = (dst.size() * 32) / pixel_bits;
  if (pixel_dst + pixel_width > dst_pixel_width) {
    pixel_width = dst_pixel_width - pixel_dst;
  }

  blit_1d_bits(dst, src, pixel_dst * pixel_bits, pixel_src * pixel_bits, pixel_width * pixel_bits, op);
}