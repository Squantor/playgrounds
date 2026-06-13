/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file test_cobs_encode.cpp
 * @brief Tests for COBS encoding, mostly taken from wikipedia article on COBS
 */
#include <minunit.h>
#include <cobs.hpp>

namespace {

Cobs cobs_dut;

MINUNIT_SETUP(cobs_encode_setup) {
  cobs_dut.reset();
  MINUNIT_PASS();
}

MINUNIT_TEARDOWN(cobs_encode_teardown) {
  MINUNIT_PASS();
}

MINUNIT_ADD(test_cobs_encode_wikipedia_cases, cobs_encode_setup, cobs_encode_teardown) {
  MINUNIT_PASS();
}

}  // namespace