/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>

void boardInit(void) {
  SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
