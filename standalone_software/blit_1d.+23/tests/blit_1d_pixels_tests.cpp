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

MINUNIT_ADD(test_blit_1d_pixels_start_copy, nullptr, nullptr) {
  // single element source start case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 6, 10, 10);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x776655EF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // double element source start case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 6, 10, 12);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x887766EF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // shift to other direction?
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 2, 14, 15);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x87ABCDEF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_pixels_copy, nullptr, nullptr) {
  // zero offset full word destination case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 8, 8);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x77665544);
  MINUNIT_CHECK(dut_dst[2] == 0xBBAA9988);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  // positive offset full word destination case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 8, 6);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x66554433);
  MINUNIT_CHECK(dut_dst[2] == 0xAA998877);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  // negative offset full word destination case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 8, 10);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x88776655);
  MINUNIT_CHECK(dut_dst[2] == 0xCCBBAA99);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  // same symmetrical offset copy case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 4, 4);
  MINUNIT_CHECK(dut_dst[0] == 0x3322CDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x77665544);
  MINUNIT_CHECK(dut_dst[2] == 0x89AB9988);
  // same assymetrical offset copy case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 6, 4);
  MINUNIT_CHECK(dut_dst[0] == 0x22ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x66554433);
  MINUNIT_CHECK(dut_dst[2] == 0x89998877);
  // not same offset copy case
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 6, 8);
  MINUNIT_CHECK(dut_dst[0] == 0x44ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x88776655);
  MINUNIT_CHECK(dut_dst[2] == 0x89BBAA99);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_pixels_small, nullptr, nullptr) {
  // small span inside word from inside word with no offset
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 4, 10, 10);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x896655EF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // small span inside word from inside word with offset
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 4, 12, 10);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x6655CDEF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // small span spanning two source words
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 4, 11, 6);
  MINUNIT_CHECK(dut_dst[0] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x84433DEF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // small span spanning two destination words
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 4, 7, 12);
  MINUNIT_CHECK(dut_dst[0] == 0x69ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x89ABC776);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  // small snap spanning two source/destination words
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 4, 7, 15);
  MINUNIT_CHECK(dut_dst[0] == 0x79ABCDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x89ABC988);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_invert, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 3, 11, Blit_ops::INVERT);
  MINUNIT_CHECK(dut_dst[0] == 0x8899ADEF);
  MINUNIT_CHECK(dut_dst[1] == 0x44556677);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABC233);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_and, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 3, 11, Blit_ops::AND);
  MINUNIT_CHECK(dut_dst[0] == 0x01224DEF);
  MINUNIT_CHECK(dut_dst[1] == 0x89AA8988);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDCC);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_or, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 3, 11, Blit_ops::OR);
  MINUNIT_CHECK(dut_dst[0] == 0xFFEFDDEF);
  MINUNIT_CHECK(dut_dst[1] == 0xBBABDDEF);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_1d_xor, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_src, 4, 16, 3, 11, Blit_ops::XOR);
  MINUNIT_CHECK(dut_dst[0] == 0xFECD9DEF);
  MINUNIT_CHECK(dut_dst[1] == 0x32015467);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABC023);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_backward, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  blit_1d_pixels(dut_dst, dut_dst, 4, 20, 12, 2);
  MINUNIT_CHECK(dut_dst[0] == 0xEF89ABEF);
  MINUNIT_CHECK(dut_dst[1] == 0xEF89ABCD);
  MINUNIT_CHECK(dut_dst[2] == 0x8989ABCD);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}

MINUNIT_ADD(test_blit_bounded, nullptr, nullptr) {
  dut_dst.fill(0x89ABCDEF);
  std::span dut_dst_sub = std::span<std::uint32_t>(dut_dst).first(2);
  blit_1d_pixels(dut_dst_sub, dut_src, 4, 32, 4, 4);
  MINUNIT_CHECK(dut_dst[0] == 0x3322CDEF);
  MINUNIT_CHECK(dut_dst[1] == 0x77665544);
  MINUNIT_CHECK(dut_dst[2] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[3] == 0x89ABCDEF);
  MINUNIT_CHECK(dut_dst[4] == 0x89ABCDEF);
}