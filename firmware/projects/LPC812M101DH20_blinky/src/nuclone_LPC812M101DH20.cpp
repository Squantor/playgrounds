/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <board.hpp>

instances::iocon::iocon<peripherals::IOCON_cpp> ioconPeripheral;
instances::swm::swm<peripherals::SWM_cpp> swmPeriperhal;
instances::gpio::gpio<peripherals::GPIO_cpp> gpioPeripheral;
instances::syscon::syscon<peripherals::SYSCON_cpp> sysconPeripheral;

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
  sysconPeripheral.enablePeripheralClocks(instances::syscon::CLOCK_SWM | instances::syscon::CLOCK_IOCON |
                                          instances::syscon::CLOCK_GPIO);
  // setup IOCON pins
  ioconPeripheral.setup(xtalInPin, registers::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, registers::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalIn);
  swmPeriperhal.setup(xtalOut, xtalOut);
  // setup system clocks
  sysconPeripheral.setSysOscControl(registers::syscon::SYSOSCCTRL::NO_BYPASS | registers::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(instances::syscon::POWER_SYSOSC);
  crudeDelay(6000);
  sysconPeripheral.selectPllClock(instances::syscon::PLLCLK_SYSOSC);
  FmcSetFlashAccess(FLASHTIM_30MHZ_CPU);
  sysconPeripheral.depowerPeripherals(instances::syscon::POWER_SYSPLL);
  sysconPeripheral.setSystemPllControl(4, instances::syscon::PLLPOSTDIV_4);
  sysconPeripheral.powerPeripherals(instances::syscon::POWER_SYSPLL);
  while (!sysconPeripheral.getSystemPllStatus())
    ;
  sysconPeripheral.setSystemClockDivider(2);
  sysconPeripheral.selectMainClock(instances::syscon::MAINCLK_PLL_OUT);
  // disable all unneeded clocks
  sysconPeripheral.disablePeripheralClocks(instances::syscon::CLOCK_IOCON);
  gpioPeripheral.output(ledPin);

  SysTick_Config(CLOCK_AHB / TICKS_PER_S);
}
