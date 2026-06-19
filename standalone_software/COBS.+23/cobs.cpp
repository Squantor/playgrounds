/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file cobs.cpp
 * @brief COBS encoder/decoder implementation
 */
#include <cstdint>
#include <cobs.hpp>

std::size_t cobs_encode(std::span<uint8_t> dst, std::span<const uint8_t> src) {
  std::uint8_t *dst_data = dst.data();
  std::uint8_t *dst_code = dst_data++;
  std::uint8_t count = 1;
  std::size_t src_len = src.size();

  for (const std::uint8_t *src_data = src.data(); src_len--; ++src_data) {
    if (*src_data) {
      // non zero data, copy and count
      *dst_data++ = *src_data;
      ++count;
    }
    if (!*src_data || count == 0xFF) {
      // input is zero, or block done, write and restart
      *dst_code = count;
      count = 1;
      dst_code = dst_data;
      if (!*src_data || src_len)
        ++dst_data;
    }
  }
  // write last data
  *dst_code = count;
  *dst_data++ = 0;

  return static_cast<std::size_t>(dst_data - dst.data());
}

/**
 * @todo Increase robustness to various corruption scenarios
 */
std::size_t cobs_decode(std::span<uint8_t> dst, std::span<const uint8_t> src) {
  const std::uint8_t *src_data = src.data();
  std::uint8_t *dst_data = dst.data();

  for (std::uint8_t code = 0xFF, cobs_idx = 0; src_data < src.data() + src.size(); --cobs_idx) {
    if (cobs_idx)
      // cobs index not reached, copy data
      *dst_data++ = *src_data++;
    else {
      // cobs index reached, check index is a zero or end of block
      cobs_idx = *src_data++;
      if (cobs_idx && (code != 0xFF))
        // index is an zero, write it down, 0xFF is a block skip
        *dst_data++ = 0;
      code = cobs_idx;
      if (!code)
        // zero found, end of decode
        break;
    }
  }

  return static_cast<std::size_t>(dst_data - (std::uint8_t *)dst.data());
}
