/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file cobs_test_values.hpp
 * @brief Test vector declarations for cobs_encode and cobs_decode
 * @note Based on the code from wikipedia.org
 */
#ifndef COBS_TEST_VALUES_HPP
#define COBS_TEST_VALUES_HPP

#include <cstdint>
#include <array>

extern std::array<const std::uint8_t, 1> data_single_zero_decoded;
extern std::array<const std::uint8_t, 3> data_single_zero_encoded;
extern std::array<const std::uint8_t, 2> data_double_zero_decoded;
extern std::array<const std::uint8_t, 4> data_double_zero_encoded;
extern std::array<const std::uint8_t, 3> data_single_data_multi_zero_decoded;
extern std::array<const std::uint8_t, 5> data_single_data_multi_zero_encoded;
extern std::array<const std::uint8_t, 4> data_multi_data_with_zero_decoded;
extern std::array<const std::uint8_t, 6> data_multi_data_with_zero_encoded;
extern std::array<const std::uint8_t, 4> data_multi_data_with_no_zero_decoded;
extern std::array<const std::uint8_t, 6> data_multi_data_with_no_zero_encoded;
extern std::array<const std::uint8_t, 4> data_multi_data_with_triple_zero_decoded;
extern std::array<const std::uint8_t, 6> data_multi_data_with_triple_zero_encoded;
extern std::array<const std::uint8_t, 254> data_big_data_decoded;
extern std::array<const std::uint8_t, 256> data_big_data_encoded;
extern std::array<const std::uint8_t, 255> data_big_data_with_zero_decoded;
extern std::array<const std::uint8_t, 257> data_big_data_with_zero_encoded;
extern std::array<const std::uint8_t, 255> data_big_data_with_overflow_decoded;
extern std::array<const std::uint8_t, 258> data_big_data_with_overflow_encoded;
extern std::array<const std::uint8_t, 255> data_big_data_with_overflow_and_zero_decoded;
extern std::array<const std::uint8_t, 258> data_big_data_with_overflow_and_zero_encoded;
extern std::array<const std::uint8_t, 255> data_big_data_with_zero_at_end_decoded;
extern std::array<const std::uint8_t, 257> data_big_data_with_zero_at_end_encoded;

#endif