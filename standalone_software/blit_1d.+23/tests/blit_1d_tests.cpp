/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file blit_1d_tests.cpp
 * @brief tests for blit_1d.hpp
 *
 */
#include "minunit.h"
#include <cstdint>
#include <array>
#include <span>
#include <blit_1d.hpp>

MINUNIT_SETUP(setup_test_blit_1d) {
  (void)test_results;
}
MINUNIT_TEARDOWN(teardown_test_blit_1d) {
  (void)test_results;
}

MINUNIT_ADD(test_blit_1d, setup_test_blit_1d, teardown_test_blit_1d) {
  std::array<std::uint32_t, 5> src;
  std::array<std::uint32_t, 5> dst;
  src.fill(0x01234567);
  dst.fill(0x89ABCDEF);
  blit_1d(src, dst, 4, 20, 0, 0);
  MINUNIT_CHECK(dst[0] == 0x01234567);
  MINUNIT_CHECK(dst[1] == 0x89ABCDE7);
  (void)test_results;
}
