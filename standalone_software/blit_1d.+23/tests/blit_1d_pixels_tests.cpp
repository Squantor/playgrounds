/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d_pixels_tests.cpp
 * @brief tests for blit_1d_pixels
 *
 */
#include "minunit.h"
#include <cstdint>
#include <array>
#include <span>
#include <blit_1d.hpp>

std::array<std::uint32_t, 5> dut_src{{0x33221100, 0x77665544, 0xBBAA9988, 0xFFEEDDCC, 0x11223344}};
std::array<std::uint32_t, 5> dut_dst;

MINUNIT_ADD(test_blit_1d_pixels_copy, nullptr, nullptr) {
  /*   // trivial copy case
    dut_dst.fill(0x89ABCDEF);
    blit_1d_pixels(dut_dst, dut_src, 4, 16, 8, 8);
    MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
    MINUNIT_CHECK(dut_dst[1] == 0x77665544);
    MINUNIT_CHECK(dut_dst[2] == 0xBBAA9988);
    MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
    // same symmetrical offset copy case
    dut_dst.fill(0x89ABCDEF);
    blit_1d_pixels(dut_dst, dut_src, 4, 16, 4, 4);
    MINUNIT_CHECK(dut_dst[0] == 0x3322CDEF);
    MINUNIT_CHECK(dut_dst[1] == 0x77665544);
    MINUNIT_CHECK(dut_dst[2] == 0x89AB9988); */
  // same assymetrical offset copy case
  /*   dut_dst.fill(0x89ABCDEF);
    blit_1d_pixels(dut_dst, dut_src, 4, 16, 6, 6);
    MINUNIT_CHECK(dut_dst[0] == 0x33ABCDEF);
    MINUNIT_CHECK(dut_dst[1] == 0x77665544);
    MINUNIT_CHECK(dut_dst[2] == 0x89AA9988); */
  // not same offset copy case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 6, 2);
  MINUNIT_CHECK(dut_dst[0] == 0x11ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x55443322);
  MINUNIT_CHECK(dut_dst[2] == 0x89887766);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
}

// tests for small spans
// tests for other operations
