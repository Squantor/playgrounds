/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file LPC810 series SWM register interface
 */
#ifndef LPC81X_SMW_REGS_HPP
#define LPC81X_SWM_REGS_HPP

namespace registers {
namespace swm {
struct registers {
  volatile uint32_t PINASSIGN[9]; /* Pin Assign register array */
  volatile uint32_t RESERVED0[103];
  volatile uint32_t PINENABLE0; /* Pin Enable register */
};
}  // namespace swm
}  // namespace registers

#endif