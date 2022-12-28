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
  /*

  // Switch clocks to their final socurces
  CLOCKS->CLK_REF_CTRL = (CLOCKS_CLK_REF_CTRL_SRC_xosc_clksrc << CLOCKS_CLK_REF_CTRL_SRC_Pos);

  CLOCKS->CLK_SYS_CTRL = (CLOCKS_CLK_SYS_CTRL_AUXSRC_clksrc_pll_sys << CLOCKS_CLK_SYS_CTRL_AUXSRC_Pos);
  CLOCKS_SET->CLK_SYS_CTRL = (CLOCKS_CLK_SYS_CTRL_SRC_clksrc_clk_sys_aux << CLOCKS_CLK_SYS_CTRL_SRC_Pos);

  CLOCKS->CLK_PERI_CTRL =
    CLOCKS_CLK_PERI_CTRL_ENABLE_Msk | (CLOCKS_CLK_PERI_CTRL_AUXSRC_clk_sys << CLOCKS_CLK_PERI_CTRL_AUXSRC_Pos);

  CLOCKS->CLK_USB_CTRL =
    CLOCKS_CLK_USB_CTRL_ENABLE_Msk | (CLOCKS_CLK_USB_CTRL_AUXSRC_clksrc_pll_usb << CLOCKS_CLK_USB_CTRL_AUXSRC_Pos);

  CLOCKS->CLK_ADC_CTRL =
    CLOCKS_CLK_ADC_CTRL_ENABLE_Msk | (CLOCKS_CLK_ADC_CTRL_AUXSRC_clksrc_pll_usb << CLOCKS_CLK_ADC_CTRL_AUXSRC_Pos);

  CLOCKS->CLK_RTC_DIV = (256 << CLOCKS_CLK_RTC_DIV_INT_Pos);  // 12MHz / 256 = 46875 Hz
  CLOCKS->CLK_RTC_CTRL =
    CLOCKS_CLK_RTC_CTRL_ENABLE_Msk | (CLOCKS_CLK_RTC_CTRL_AUXSRC_xosc_clksrc << CLOCKS_CLK_ADC_CTRL_AUXSRC_Pos);

  // Configure 1 us tick for watchdog and timer
  WATCHDOG->TICK = ((F_REF / F_TICK) << WATCHDOG_TICK_CYCLES_Pos) | WATCHDOG_TICK_ENABLE_Msk;

  */

  timeout = resetsReset(RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK, 0x1000000);

  // setup LED pin
  sioGpioOeSet(SIO, LED_MASK);
  iobank0GpioCtrl(IO_BANK0, LED_PIN, BANK0_GPIO25_FUNC_SIO, 0);
  //  setup systick
  SysTick_Config(CLOCK_CPU / TICKS_PER_S);
}
