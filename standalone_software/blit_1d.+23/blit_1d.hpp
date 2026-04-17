/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d.hpp
 * @brief 1D blit routines
 * @version 20260403
 * @todo Maybe we could use a function that has the whole switch case of operations in it
 *
 */
#ifndef BLIT_1D_HPP
#define BLIT_1D_HPP

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
 * @brief Blit operation
 * @param dst
 * @param src
 * @param src_bit
 * @param dst_bit
 * @param bit_width
 * @param op
 */
void blit_op(std::uint32_t &dst, std::uint32_t src, std::uint32_t mask, Blit_ops op);

void blit_1d_bits(std::span<std::uint32_t> dst, std::span<std::uint32_t> src, size_t src_bit, size_t dst_bit, size_t bit_width,
                  Blit_ops op = Blit_ops::COPY);

/**
 * @brief 1D blit
 * @param src Source array of pixels
 * @param dst Destination array of pixels
 * @param pixel_bits Bits per pixel
 * @param pixel_width Width of pixels to blit
 * @param pixel_src Source pixel index of the blit
 * @param pixel_dst Destination pixel index of the blit
 */
void blit_1d_pixels(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t pixel_bits, std::size_t pixel_width,
                    std::size_t pixel_src, std::size_t pixel_dst, Blit_ops op = Blit_ops::COPY);

#endif