/*
MIT License

Copyright (c) 2020 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <board.hpp>

void crudeDelay(uint32_t iterations) {
  for (uint32_t i = iterations; i > 0; i--) {
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    __NOP();
  }
}

void boardInit(void) {
  // clock enables and resets
  sysconEnableClocks(SYSCON, CLKCTRL_SWM | CLKCTRL_IOCON | CLKCTRL_GPIO);
  sysconAssertResets(SYSCON, RESETCTRL_I2C);
  sysconClearResets(SYSCON, RESETCTRL_I2C);
  // setup io pins
  ioconSetupPin(IOCON, IOCON_XTAL_IN, IOCON_MODE(PIN_INACTIVE));
  ioconSetupPin(IOCON, IOCON_XTAL_OUT, IOCON_MODE(PIN_INACTIVE));
  ioconSetupPin(IOCON, IOCON_LED, IOCON_MODE(PIN_INACTIVE));
  swmEnableFixedPin(SWM, SWM_EN0_XTALIN | SWM_EN0_XTALOUT);
  sysconDisableClocks(SYSCON, CLKCTRL_SWM | CLKCTRL_IOCON);

  // setup system clocks
  sysconSysOscControl(SYSCON, SYSOSCCTRL_BYPASS(0) | SYSOSCCTRL_FREQ_1_20MHZ);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSOSC);
  crudeDelay(6000);
  sysconSysPllClockSelect(SYSCON, SYSPLLCLKSEL_SYSOSC);
  FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);
  sysconPowerDisable(SYSCON, PDRUNCFG_SYSPLL);
  sysconPllControl(SYSCON, 4, SYSPLLCTRL_POSTDIV_4);
  sysconPowerEnable(SYSCON, PDRUNCFG_SYSPLL);
  while (!sysconPllStatus(SYSCON))
    ;
  sysconMainClockDivider(SYSCON, 2);
  sysconMainClockSelect(SYSCON, MAINCLKSEL_PLL_OUT);

  // setup led pin
  gpioSetPinDIROutput(GPIO, PORT_LED, PIN_LED);
  gpioPinWrite(GPIO, PORT_LED, PIN_LED, 0);
  SysTick_Config(CLOCK_AHB / TICKS_PER_S);

  // setup SPI
}
