/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file cobs.hpp
 * @brief COBS encoder/decoder definitions
 * @note Based on the code from wikipedia.org
 */
#ifndef COBS_HPP
#define COBS_HPP

#include <cstdint>
#include <span>

/**
 * @brief Encodes data using COBS
 * @param dst Where to put encoded data
 * @param src Decoded data to encode
 * @return Encoded buffer length in bytes
 */
std::size_t cobs_encode(std::span<uint8_t> dst, std::span<const uint8_t> src);

/**
 * @brief Decodes data using COBS
 * @param dst Where to put decoded data
 * @param src Encoded data to decode
 * @return std::size_t 
 */
std::size_t cobs_decode(std::span<uint8_t> dst, std::span<const uint8_t> src);

#endif
