/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file test_cobs_decode.cpp
 * @brief Tests for COBS decoding, mostly taken from wikipedia article on COBS
 */
#include <cstdint>
#include <minunit.h>
#include <cobs_test_values.hpp>
#include <cobs.hpp>

namespace {

MINUNIT_ADD(test_single_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 5> test_output;
  std::size_t result = cobs_decode(test_output, data_single_zero_encoded);
  MINUNIT_ASSERT(result == 1);
  for (std::size_t index = 0; index < data_single_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_single_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_double_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 5> test_output;
  std::size_t result = cobs_decode(test_output, data_double_zero_encoded);
  MINUNIT_ASSERT(result == 2);
  for (std::size_t index = 0; index < data_double_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_double_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_single_data_multi_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 5> test_output;
  std::size_t result = cobs_decode(test_output, data_single_data_multi_zero_encoded);
  MINUNIT_ASSERT(result == 3);
  for (std::size_t index = 0; index < data_single_data_multi_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_single_data_multi_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_multi_data_with_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 8> test_output;
  std::size_t result = cobs_decode(test_output, data_multi_data_with_zero_encoded);
  MINUNIT_ASSERT(result == 4);
  for (std::size_t index = 0; index < data_multi_data_with_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_multi_data_with_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_multi_data_with_no_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 8> test_output;
  std::size_t result = cobs_decode(test_output, data_multi_data_with_no_zero_encoded);
  MINUNIT_ASSERT(result == 4);
  for (std::size_t index = 0; index < data_multi_data_with_no_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_multi_data_with_no_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_multi_data_with_triple_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 8> test_output;
  std::size_t result = cobs_decode(test_output, data_multi_data_with_triple_zero_encoded);
  MINUNIT_ASSERT(result == 4);
  for (std::size_t index = 0; index < data_multi_data_with_triple_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_multi_data_with_triple_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_big_data_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 300> test_output;
  std::size_t result = cobs_decode(test_output, data_big_data_encoded);
  MINUNIT_ASSERT(result == 254);
  for (std::size_t index = 0; index < data_big_data_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_big_data_decoded[index]);
  }
}

MINUNIT_ADD(test_big_data_with_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 300> test_output;
  std::size_t result = cobs_decode(test_output, data_big_data_with_zero_encoded);
  MINUNIT_ASSERT(result == 255);
  for (std::size_t index = 0; index < data_big_data_with_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_big_data_with_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_big_data_with_overflow_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 300> test_output;
  std::size_t result = cobs_decode(test_output, data_big_data_with_overflow_encoded);
  MINUNIT_ASSERT(result == 255);
  for (std::size_t index = 0; index < data_big_data_with_overflow_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_big_data_with_overflow_decoded[index]);
  }
}

MINUNIT_ADD(test_big_data_with_overflow_and_zero_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 300> test_output;
  std::size_t result = cobs_decode(test_output, data_big_data_with_overflow_and_zero_encoded);
  MINUNIT_ASSERT(result == 255);
  for (std::size_t index = 0; index < data_big_data_with_overflow_and_zero_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_big_data_with_overflow_and_zero_decoded[index]);
  }
}

MINUNIT_ADD(test_big_data_with_zero_at_end_cpp, nullptr, nullptr) {
  std::array<std::uint8_t, 300> test_output;
  std::size_t result = cobs_decode(test_output, data_big_data_with_zero_at_end_encoded);
  MINUNIT_ASSERT(result == 255);
  for (std::size_t index = 0; index < data_big_data_with_zero_at_end_decoded.size(); index++) {
    MINUNIT_ASSERT(test_output[index] == data_big_data_with_zero_at_end_decoded[index]);
  }
}

}  // namespace