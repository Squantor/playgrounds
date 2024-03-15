/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <systick.hpp>

uint32_t sysTick = 0;

extern "C" {
void SysTick_Handler(void) {
  sysTick++;
}
}