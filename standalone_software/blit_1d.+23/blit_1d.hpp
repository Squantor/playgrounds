/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d.h
 * @brief 1D blit routines
 * @version 20260403
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
  (void)src;
  (void)dst;
  (void)pixel_bits;
  (void)pixel_width;
  (void)pixel_src;
  (void)pixel_dst;
  (void)op;
}

#endif