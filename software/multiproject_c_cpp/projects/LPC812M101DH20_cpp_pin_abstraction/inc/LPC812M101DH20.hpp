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

namespace peripherals {
constexpr static inline uint32_t IOCON_cpp = 0x4004'4000u; /**< TODO, rename to their names when refactoring is done */
constexpr static inline uint32_t SWM_cpp = 0x4000'C000u;   /**< TODO, rename to their names when refactoring is done */
}  // namespace peripherals

// includes that define the registers namespace go here.
#include <LPC8xx.hpp/LPC81X_iocon_regs.hpp>
#include <LPC8xx.hpp/LPC81X_swm_regs.hpp>

// device specific headers go here
// these need to go after registers namespace definitions as they are used here
#include <LPC8xx.hpp/LPC812M101DH20_pins.hpp>

// includes that use the registers namespace go here
// need to go after registers namespaces and device specific headers
#include <LPC8xx.hpp/LPC81X_iocon.hpp>
#include <LPC8xx.hpp/LPC81X_swm.hpp>

#endif