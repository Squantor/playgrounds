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
#include <blits.hpp>

namespace {

MINUNIT_ADD(test_blit_op_copy, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  const std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0x0, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xFFFFFFFF, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x89ABCDEF);
  dst = 0x01234567;
  blit_op(dst, src, 0x0F, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x0123456F);
  dst = 0x01234567;
  blit_op(dst, src, 0xF0F0F0F0, Blit_ops::COPY);
  MINUNIT_CHECK(dst == 0x81A3C5E7);
}

MINUNIT_ADD(test_blit_op_invert, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  const std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0x0, Blit_ops::INVERT);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xFFFFFFFF, Blit_ops::INVERT);
  MINUNIT_CHECK(dst == 0x76543210);
  dst = 0x01234567;
  blit_op(dst, src, 0x0F, Blit_ops::INVERT);
  MINUNIT_CHECK(dst == 0x01234560);
  dst = 0x01234567;
  blit_op(dst, src, 0xF0F0F0F0, Blit_ops::INVERT);
  MINUNIT_CHECK(dst == 0x71533517);
}

MINUNIT_ADD(test_blit_op_and, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  const std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0x0, Blit_ops::AND);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xFFFFFFFF, Blit_ops::AND);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0x0F, Blit_ops::AND);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xF0F0F0F0, Blit_ops::AND);
  MINUNIT_CHECK(dst == 0x01234567);
}

MINUNIT_ADD(test_blit_op_or, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  const std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0x0, Blit_ops::OR);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xFFFFFFFF, Blit_ops::OR);
  MINUNIT_CHECK(dst == 0x89ABCDEF);
  dst = 0x01234567;
  blit_op(dst, src, 0x0F, Blit_ops::OR);
  MINUNIT_CHECK(dst == 0x0123456F);
  dst = 0x01234567;
  blit_op(dst, src, 0xF0F0F0F0, Blit_ops::OR);
  MINUNIT_CHECK(dst == 0x81A3C5E7);
}

MINUNIT_ADD(test_blit_op_xor, nullptr, nullptr) {
  std::uint32_t dst = 0x01234567;
  const std::uint32_t src = 0x89ABCDEF;
  blit_op(dst, src, 0x0, Blit_ops::XOR);
  MINUNIT_CHECK(dst == 0x01234567);
  dst = 0x01234567;
  blit_op(dst, src, 0xFFFFFFFF, Blit_ops::XOR);
  MINUNIT_CHECK(dst == 0x88888888);
  dst = 0x01234567;
  blit_op(dst, src, 0x0F, Blit_ops::XOR);
  MINUNIT_CHECK(dst == 0x01234568);
  dst = 0x01234567;
  blit_op(dst, src, 0xF0F0F0F0, Blit_ops::XOR);
  MINUNIT_CHECK(dst == 0x81838587);
}

}  // namespace