/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#ifndef GENERIC_BOARD_HPP
#define GENERIC_BOARD_HPP

#define CLOCK_XTAL (12000000u)
#define CLOCK_CPU (120000000u)

#include <mcu_ll.h>

#define TICKS_PER_S (8u)

void boardInit(void);

#define LED_PIN BANK0_GPIO25
#define LED_MASK BANK0_GPIO25_MASK

#endif