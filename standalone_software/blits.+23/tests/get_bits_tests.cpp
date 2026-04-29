/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file get_bits_tests.cpp
 * @brief tests for get_bits
 *
 */
#include "minunit.h"
#include <cstdint>
#include <array>
#include <span>
#include <blits.hpp>

std::array<const std::uint32_t, 5> dut_src_get_bits{{0x33221100, 0x77665544, 0xBBAA9988, 0xFFEEDDCC, 0x11223344}};

namespace {

MINUNIT_ADD(test_get_bits, nullptr, nullptr) {
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 0) == 0x33221100);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 4) == 0x43322110);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 16) == 0x55443322);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 32) == 0x77665544);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 40) == 0x88776655);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 128) == 0x11223344);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 144) == 0x00001122);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 160) == 0x00000000);
  MINUNIT_CHECK(detail::get_bits(dut_src_get_bits, 192) == 0x00000000);
}

}  // namespace
