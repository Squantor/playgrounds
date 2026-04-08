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

MINUNIT_ADD(test_blit_op_copy, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x89ABCDEF);
  dst = 0x01234567;
  blit_op(dst, src, 4, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x9ABCDEF7);
  dst = 0x01234567;
  blit_op(dst, src, -4, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x089ABCDE);
  dst = 0x01234567;
  blit_op(dst, src, 24, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0xEF234567);
  (void)test_results;
}