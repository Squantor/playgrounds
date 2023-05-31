/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/* Main entry point for the LPC812M101DH20 microcontroller definitions */
#ifndef LPC812M101DH20_HPP
#define LPC812M101DH20_HPP

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/*
Copied orignally from the C header, the idea is to move more and more from
C definitions to C++. Step by step, C++ bits will go below
*/

namespace peripherals {
constexpr static inline uint32_t SPI0_cpp = 0x4005'8000u; /**< TODO, rename to their names when refactoring is done */
constexpr static inline uint32_t SPI1_cpp = 0x4005'C000u; /**< TODO, rename to their names when refactoring is done */
}  // namespace peripherals

namespace instances {

/**
 * @brief Available pins on LPC812M101DH20
 *
 */
enum IOpins : uint8_t {
  PIN00,
  PIN01,
  PIN02,
  PIN03,
  PIN04,
  PIN05,
  PIN06,
  PIN07,
  PIN08,
  PIN09,
  PIN10,
  PIN11,
  PIN12,
  PIN13,
  PIN14,
  PIN15,
  PIN16,
  PIN17,
};

/**
 * @brief Available ports on LPC812M101DH20
 *
 */
enum IOports : uint8_t {
  PORT0,
};

}  // namespace instances

// device specific headers go here
#include <LPC8xx.hpp/LPC81X_pins.hpp>

// includes that define the registers namespace go here.
#include <LPC8xx.hpp/LPC81X_iocon_regs.hpp>

// includes that use the registers namespace go here
#include <LPC8xx.hpp/LPC81X_iocon.hpp>

#endif