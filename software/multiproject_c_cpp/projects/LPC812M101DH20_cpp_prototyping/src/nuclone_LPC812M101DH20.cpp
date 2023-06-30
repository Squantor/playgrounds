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
#include <nuclone_LPC812M101DH20.hpp>

constexpr xtalInPinType xtalInPin;
constexpr xtalOutPinType xtalOutPin;
constexpr test0PinType test0Pin;
constexpr test1PinType test1Pin;
constexpr test2PinType test2Pin;
constexpr i2cSclOutPinType i2cSclOutPin;
constexpr i2cSdaOutPinType i2cSdaOutPin;
constexpr i2cSclSensePinType i2cSclSensePin;
constexpr i2cSdaSensePinType i2cSdaSensePin;

constexpr mainI2cSclFunctionType i2cMainSclFunction;
constexpr mainI2cSdaFunctionType i2cMainSdaFunction;
constexpr xtalInFunctionType xtalIn;
constexpr xtalOutFunctionType xtalOut;

instances::iocon::iocon<peripherals::IOCON_cpp> ioconPeripheral;
instances::swm::swm<peripherals::SWM_cpp> swmPeriperhal;

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
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(i2cSclSensePin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(i2cSdaSensePin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(i2cSclOutPin, registers::iocon::i2cmodes::I2C_STD);
  ioconPeripheral.setup(i2cSdaOutPin, registers::iocon::i2cmodes::I2C_STD);
  ioconPeripheral.setup(test0Pin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(test1Pin, registers::iocon::pullModes::PULLUP);
  ioconPeripheral.setup(test2Pin, registers::iocon::pullModes::PULLUP);
  swmPeriperhal.setup(i2cSclOutPin, i2cMainSclFunction);
  swmPeriperhal.setup(i2cSdaOutPin, i2cMainSdaFunction);
  swmPeriperhal.setup(xtalInPin, xtalIn);
  swmPeriperhal.setup(xtalOut, xtalOut);

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

  SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}

void ledState(bool isOn) {
  if (isOn)
    ioconPeripheral.setup(test2Pin, registers::iocon::pullModes::PULLUP);
  else
    ioconPeripheral.setup(test2Pin, registers::iocon::pullModes::PULLDOWN);
}