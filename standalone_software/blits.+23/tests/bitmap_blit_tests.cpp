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
#include <blits.hpp>

std::array<const std::uint32_t, 8> dut_bitmap_src_data{
  {0x33221100, 0x77665544, 0xBBAA9988, 0xFFEEDDCC, 0x1F2E3D4C, 0x5F6E7D8C, 0x9FAEBDBC, 0xFFEEDDCC}};
std::array<std::uint32_t, 12> dut_bitmap_dst_data;

namespace {

MINUNIT_ADD(test_bitmap_blit_inside, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{4, 4}, 4);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 4);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{2, 2});
  MINUNIT_CHECK(dut_bitmap_dst_data[1] == 0xCCCC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[2] == 0xCC110055);
  MINUNIT_CHECK(dut_bitmap_dst_data[3] == 0xCC332255);
  MINUNIT_CHECK(dut_bitmap_dst_data[4] == 0xCC554455);
  MINUNIT_CHECK(dut_bitmap_dst_data[5] == 0xCC776655);
  MINUNIT_CHECK(dut_bitmap_dst_data[6] == 0xCCCC5555);
}

MINUNIT_ADD(test_bitmap_blit_outside, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{4, 4}, 4);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 4);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{8, 8});
  for (const auto &element : dut_bitmap_dst_data) {
    MINUNIT_CHECK(element == 0xCCCC5555);
  }
}

MINUNIT_ADD(test_bitmap_blit_outside_corner, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{4, 4}, 4);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 4);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{6, 6});
  MINUNIT_CHECK(dut_bitmap_dst_data[5] == 0xCCCC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[6] == 0x00CC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[7] == 0x22CC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[8] == 0xCCCC5555);
}

MINUNIT_ADD(test_bitmap_blit_src_bounded, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{4, 4}, 4);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 4);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{4, 4}, Bitmap_coords{1, 1}, Bitmap_size{2, 2});
  MINUNIT_CHECK(dut_bitmap_dst_data[3] == 0xCCCC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[4] == 0xCC325555);
  MINUNIT_CHECK(dut_bitmap_dst_data[5] == 0xCC545555);
  MINUNIT_CHECK(dut_bitmap_dst_data[6] == 0xCCCC5555);
}

MINUNIT_ADD(test_bitmap_blit_src_bounded_outside_corner, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{4, 4}, 4);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 4);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{6, 6}, Bitmap_coords{1, 1}, Bitmap_size{3, 3});
  MINUNIT_CHECK(dut_bitmap_dst_data[5] == 0xCCCC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[6] == 0x32CC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[7] == 0x54CC5555);
  MINUNIT_CHECK(dut_bitmap_dst_data[8] == 0xCCCC5555);
}

// Copy a 1 bit bitmap to a 1 bit bitmap on a specific location
MINUNIT_ADD(test_bitmap_blit_1bit, nullptr, nullptr) {
  const Const_bitmap dut_bitmap_src(dut_bitmap_src_data.data(), Bitmap_size{8, 32}, 1);
  const Bitmap dut_bitmap_dst(dut_bitmap_dst_data.data(), Bitmap_size{8, 8}, 1);
  dut_bitmap_dst_data.fill(0xCCCC5555);
  blit_bitmap(dut_bitmap_dst, dut_bitmap_src, Bitmap_coords{0, 0}, Bitmap_coords{0, 16}, Bitmap_size{8, 8});
  MINUNIT_CHECK(dut_bitmap_dst_data[0] == 0x1F2E3D4C);
  MINUNIT_CHECK(dut_bitmap_dst_data[1] == 0x5F6E7D8C);
}

// Copy a bounded 1 bit bitmap to a 1 bit bitmap on a specific location
}  // namespace