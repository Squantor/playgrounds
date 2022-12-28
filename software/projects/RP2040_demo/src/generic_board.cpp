/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <generic_board.hpp>

void boardInit(void) {
  volatile uint32_t timeout = 0;
  (void)timeout;
  // ~1 ms @ 12 MHz
  timeout = xoscStart(47, 0x1000000);

  // Setup SYS PLL for 12 MHz * 40 / 4 / 1 = 120 MHz
  timeout = resetsReset(RESETS_PLL_SYS_MASK, 0x1000000);
  timeout = pllStart(PLL_SYS, 1, 40, 4, 1, 0x1000000);

  // Setup USB PLL for 12 MHz * 36 / 3 / 3 = 48 MHz
  timeout = resetsReset(RESETS_PLL_USB_MASK, 0x1000000);
  timeout = pllStart(PLL_USB, 1, 36, 3, 3, 0x1000000);

  // Switch clocks to their final socurces
  CLOCKS->CLK[CLK_REF].CTRL = CLOCKS_CLK_CTRL_SRC(REF_SRC_XOSC);

  CLOCKS->CLK[CLK_SYS].CTRL = CLOCKS_CLK_CTRL_AUXSRC(SYS_AUXSRC_PLL_SYS);
  CLOCKS_SET->CLK[CLK_SYS].CTRL = CLOCKS_CLK_CTRL_SRC(SYS_SRC_CLKSRC_CLK_SYS_AUX);

  CLOCKS->CLK[CLK_PERI].CTRL = CLOCKS_CLK_CTRL_ENABLE | CLOCKS_CLK_CTRL_AUXSRC(PERI_AUXSRC_CLK_SYS);

  CLOCKS->CLK[CLK_USB].CTRL = CLOCKS_CLK_CTRL_ENABLE | CLOCKS_CLK_CTRL_AUXSRC(USB_AUXSRC_PLL_USB);

  CLOCKS->CLK[CLK_ADC].CTRL = CLOCKS_CLK_CTRL_ENABLE | CLOCKS_CLK_CTRL_AUXSRC(ADC_AUXSRC_PLL_USB);

  CLOCKS->CLK[CLK_RTC].DIV = CLOCKS_CLK_DIV_INT(256);  // 12MHz / 256 = 46875 Hz
  CLOCKS->CLK[CLK_RTC].CTRL = CLOCKS_CLK_CTRL_ENABLE | CLOCKS_CLK_CTRL_AUXSRC(RTC_AUXSRC_XOSC);

  /*

  // Configure 1 us tick for watchdog and timer
  WATCHDOG->TICK = ((F_REF / F_TICK) << WATCHDOG_TICK_CYCLES_Pos) | WATCHDOG_TICK_ENABLE_Msk;

  */
  // TODO: verify clock signals

  timeout = resetsReset(RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK, 0x1000000);

  // setup LED pin
  sioGpioOeSet(SIO, LED_MASK);
  iobank0GpioCtrl(IO_BANK0, LED_PIN, BANK0_GPIO25_FUNC_SIO, 0);
  //  setup systick
  SysTick_Config(CLOCK_CPU / TICKS_PER_S);
}
