/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blits.hpp
 * @brief Various bit blit functions
 * @version 20260403
 *
 */
#ifndef BLITS_HPP
#define BLITS_HPP

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

namespace detail {
std::uint32_t get_bits(std::span<std::uint32_t> src, std::size_t src_bit);
}  // namespace detail

/**
 * @brief Blit operating on single uint32_t
 * @param dst Destination to perform operation on
 * @param src Source data
 * @param mask Mask for operation, set bits will perform operation
 * @param op Operation to perform
 */
void blit_op(std::uint32_t &dst, std::uint32_t src, std::uint32_t mask, Blit_ops op);

/**
 * @brief 1D blit operating on bits only
 * @param dst Span of uint32_t's containing the destination bits
 * @param src Span of uint32_t's containing the source bits
 * @param dst_bit Destination bit index for dst
 * @param src_bit Source bit index for src
 * @param bit_width Number of bits to blit
 * @param op Blit operation
 */
void blit_1d_bits(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t dst_bit, size_t src_bit, size_t bit_width,
                  Blit_ops op = Blit_ops::COPY);

/**
 * @brief 1D blit operating on pixels, each pixel is one or more bits
 * @param src Span of uint32_t's containing the source pixels
 * @param dst Span of uint32_t's containing the destination pixels
 * @param pixel_bits Bits per pixel
 * @param pixel_width Width of pixels to blit
 * @param pixel_src Source pixel index of the blit
 * @param pixel_dst Destination pixel index of the blit
 * @param op Blit operation
 */
void blit_1d_pixels(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
                    std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op = Blit_ops::COPY);

#endif