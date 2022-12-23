/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <generic_board.hpp>

void boardInit(void) {
  // Enable XOSC
  XOSC->CTRL = XOSC_CTRL_DIS | XOSC_CTRL_FREQ_RANGE_1_15MHZ;
  XOSC->STARTUP = 47;  // ~1 ms @ 12 MHz
  XOSC->CTRL = XOSC_CTRL_EN | XOSC_CTRL_FREQ_RANGE_1_15MHZ;
  while (0 == (XOSC->STATUS & XOSC_STATUS_ENABLED_MASK))
    ;

  resetsReset(RESETS_CLR, RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK);
  while (resetsGetResetDone(RESETS, RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK) ==
         (RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK))
    ;
  // setup LED pin
  sioGpioOeSet(SIO, LED_MASK);
  iobank0GpioCtrl(IO_BANK0, LED_PIN, BANK0_GPIO25_FUNC_SIO, 0);
  //  setup systick
  SysTick_Config(CLOCK_CPU / TICKS_PER_S);
}
