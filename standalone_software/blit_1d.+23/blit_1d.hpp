/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d.h
 * @brief 1D blit routines
 * @version 20260403
 * @todo Maybe we could use a function that has the whole switch case of operations in it
 *
 */
#ifndef BLIT_1D_H
#define BLIT_1D_H

#include <cstdint>
#include <span>

/**
 * @brief Blit operations
 */
enum class Blit_ops {
  COPY,   /*!< Copy */
  INVERT, /*!< Invert */
  AND,    /*!< AND */
  OR,     /*!< OR */
  XOR,    /*!< XOR */
};

/**
 * @brief 1D blit
 * @param src Source array of pixels
 * @param dst Destination array of pixels
 * @param pixel_bits Bits per pixel
 * @param pixel_width Width of pixels to blit
 * @param pixel_src Source pixel index of the blit
 * @param pixel_dst Destination pixel index of the blit
 */
void blit_1d(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
             std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op = Blit_ops::COPY) {
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

#endif