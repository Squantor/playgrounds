/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file test_bitmap.cpp
 * @brief Tests for bitmap class
 */
#include <cstdint>
#include <array>
#include <bitmap.hpp>
#include <minunit.h>

std::array<const std::uint32_t, 8> dut_bitmap_src_data{
  {0x33221100, 0x77665544, 0xBBAA9988, 0xFFEEDDCC, 0x1F2E3D4C, 0x5F6E7D8C, 0x9FAEBDBC, 0xFFEEDDCC}};
std::array<std::uint32_t, 8> dut_bitmap_dst_data;

namespace {
// Copy a 4 bit bitmap to a 4 bit bitmap on a specific location
// Copy a bounded 4 bit bitmap to a 4 bit bitmap on a specific location
// Copy a 1 bit bitmap to a 1 bit bitmap on a specific location
// Copy a bounded 1 bit bitmap to a 1 bit bitmap on a specific location
}