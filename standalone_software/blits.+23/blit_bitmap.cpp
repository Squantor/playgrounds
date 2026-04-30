/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_bitmap.hpp
 * @brief bitmap blit functions
 * @version 20260430
 *
 */

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <span>
#include <utility>
#include "blits.hpp"
#include "bitmap.hpp"

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Blit_ops op) {
  (void)dst;
  (void)src;
  (void)dst_x;
  (void)dst_y;
  (void)op;
}

void blit_bitmap(Bitmap dst, Const_bitmap src, Bitmap_coord dst_x, Bitmap_coord dst_y, Bitmap_coord src_x, Bitmap_coord src_y,
                 Bitmap_size width, Bitmap_size height, Blit_ops op) {
  (void)dst;
  (void)src;
  (void)dst_x;
  (void)dst_y;
  (void)src_x;
  (void)src_y;
  (void)width;
  (void)height;
  (void)op;
}