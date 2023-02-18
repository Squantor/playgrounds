/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief RP2040 demonstration init
 *
 */
#include <nuclone_RP2040.hpp>

void boardInit(void) {
  // reset all setup peripherals
  resetsReset(RESETS_IO_BANK0_MASK | RESETS_PADS_BANK0_MASK | RESETS_PLL_SYS_MASK | RESETS_PLL_USB_MASK | RESETS_UART0_MASK |
                RESETS_UART1_MASK | RESETS_SPI0_MASK | RESETS_PIO1_MASK,
              0x1000000);
  // clear resusitator status
  CLOCKS_SET->CLK_SYS_RESUS_CTRL = CLOCKS_SYS_RESUS_CTRL_CLEAR;
  // 47 ticks is around 1 ms @ 12 MHz
  xoscStart(47, 0x1000000);

  // Setup PLL's
  // atadarov config: 12MHz * 40 / 4 / 1 = 120MHz
  pllStart(PLL_SYS, 1, 40, 4, 1, 0x1000000);
  // SDK config: 12MHz * 125 / 6 / 2 = 125MHz
  // pllStart(PLL_SYS, 1, 125, 6, 2, 0x1000000);
  // atadarov config: 12 MHz * 36 / 3 / 3 = 48MHz
  pllStart(PLL_USB, 1, 36, 3, 3, 0x1000000);
  // SDK config: 12MHz * 100 / 5 / 5 = 48MHz
  // pllStart(PLL_USB, 1, 100, 5, 5, 0x1000000);

  // Setup clocks
  clocksSwitchGlitchlessSrc(CLK_REF, REF_SRC_XOSC, 0x1000000);
  clocksSwitchGlitchlessAux(CLK_SYS, SYS_AUXSRC_PLL_SYS, 0x1000000);
  clockSwitchBasicAux(CLK_PERI, PERI_AUXSRC_CLK_SYS);
  clockSwitchBasicAux(CLK_USB, USB_AUXSRC_PLL_USB);
  clockSwitchBasicAux(CLK_ADC, ADC_AUXSRC_PLL_USB);
  clocksSetDivider(CLK_RTC, 256, 0);  // 12MHz / 256 = 46875 Hz
  clockSwitchBasicAux(CLK_RTC, RTC_AUXSRC_XOSC);
  // output clock network to GPOUT0, very useful for clock debugging
  // clocksSetDivider(CLK_GPOUT0, 10, 0);  // divide by 10 to make math easier
  // clockSwitchBasicAux(CLK_GPOUT0, GPOUT0_AUXSRC_CLK_USB);
  // iobank0GpioCtrl(IO_BANK0, CLOCK_PIN, BANK0_GPIO21_FUNC_CLOCK_GPOUT0, 0);
  /*
  // Configure 1 us tick for watchdog and timer
  WATCHDOG->TICK = ((F_REF / F_TICK) << WATCHDOG_TICK_CYCLES_Pos) | WATCHDOG_TICK_ENABLE_Msk;
  */
  // setup I2C
  i2cSetupMaster(I2C0, IC_CON_SPEED_FASTMODE, 400000);
  // setup UART
  uartSetBaudRate(UART0, 115200);
  uartSetFormat(UART0, UART_8DATA_BITS, UART_1STOP_BIT, UART_PARITY_NONE);
  uartEnable(UART0);
  // setup SPI
  spiSetup(SPI0, SSP_FORMAT_MOTOROLA, SSP_PHASE_SPH0_SPO0, 8, 1000000);
  spiEnable(SPI0, false);

  // setup LED pin
  sioGpioOeSet(SIO, LED_MASK);
  iobank0GpioCtrl(IO_BANK0, LED_PIN, BANK0_GPIO25_FUNC_SIO, 0);
  // Setup UART 0 pins
  iobank0GpioCtrl(IO_BANK0, UART_RX_PIN, BANK0_GPIO0_FUNC_UART0_TX, 0);
  iobank0GpioCtrl(IO_BANK0, UART_TX_PIN, BANK0_GPIO1_FUNC_UART0_RX, 0);
  // Setup SPI 0 pins
  iobank0GpioCtrl(IO_BANK0, SPI_SCK_PIN, BANK0_GPIO2_FUNC_SPI0_SCK, 0);
  iobank0GpioCtrl(IO_BANK0, SPI_MOSI_PIN, BANK0_GPIO3_FUNC_SPI0_TX, 0);
  iobank0GpioCtrl(IO_BANK0, SPI_MISO_PIN, BANK0_GPIO4_FUNC_SPI0_RX, 0);
  iobank0GpioCtrl(IO_BANK0, SPI_CS_PIN, BANK0_GPIO5_FUNC_SPI0_CS, 0);
  // Setup I2C 0 pins
  iobank0GpioCtrl(IO_BANK0, I2C_SCL_PIN, BANK0_GPIO9_FUNC_I2C0_SCL, 0);
  iobank0GpioCtrl(IO_BANK0, I2C_SDA_PIN, BANK0_GPIO8_FUNC_I2C0_SDA, 0);

  //  setup systick
  SysTick_Config(FREQ_CPU / TICKS_PER_S);
  __enable_irq();
}
