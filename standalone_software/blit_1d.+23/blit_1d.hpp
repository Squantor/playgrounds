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

void blit_1d(std::span<std::uint32_t> src, std::span<std::uint32_t> dst, std::size_t bbp, std::size_t pixel_width,
             std::size_t pixel_src, std::size_t pixel_dst) {
  (void)src;
  (void)dst;
  (void)bbp;
  (void)width;
  (void)src_offset;
  (void)dst_offset;
}

#endif