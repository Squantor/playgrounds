/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief board initialization code for LPC845 small nuclone
 */
#include <nuclone_LPC845BD48_small.hpp>

libmcull::iocon::Iocon<libmcuhw::IoconAddress> ioconPeripheral;
libmcull::swm::Swm<libmcuhw::SwmAddress> swmPeriperhal;
libmcull::gpio::Gpio<libmcuhw::GpioAddress> gpioPeripheral;
libmcull::syscon::Syscon<libmcuhw::SysconAddress> sysconPeripheral;
libmcull::systick::Systick<libmcuhw::systick_address> systickPeripheral;

auto systickIsrLambda = []() {
  gpioPeripheral.toggle(ledPin);
};

void boardInit(void) {
  // clock enables and resets
  sysconPeripheral.enablePeripheralClocks(libmcull::syscon::peripheralClocks0::SWM | libmcull::syscon::peripheralClocks0::IOCON |
                                            libmcull::syscon::peripheralClocks0::GPIO0 | libmcull::syscon::peripheralClocks0::GPIO1,
                                          0);
  // setup IOCON pins
  ioconPeripheral.setup(ledPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalInPin, libmcull::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libmcull::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  // setup crystal oscillator
  sysconPeripheral.setSysOscControl(libmcuhw::syscon::SYSOSCCTRL::NO_BYPASS | libmcuhw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(libmcull::syscon::powerOptions::SYSOSC);
  libMcu::sw::delay(3000);
  // setup PLL
  sysconPeripheral.selectPllClock(libmcull::syscon::pllClockSources::EXT);
  sysconPeripheral.depowerPeripherals(libmcull::syscon::powerOptions::SYSPLL);
  sysconPeripheral.setSystemPllControl(4, libmcull::syscon::pllPostDivider::DIV_4);
  sysconPeripheral.powerPeripherals(libmcull::syscon::powerOptions::SYSPLL);
  while (sysconPeripheral.getSystemPllStatus() == 0)
    ;
  sysconPeripheral.setSystemClockDivider(2);
  // switch mainclock
  // sysconPeripheral.selectMainClock(libmcull::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  sysconPeripheral.selectMainPllClock(libmcull::syscon::mainClockPllSources::SYSPLL);
  // setup clock out test pin
  swmPeriperhal.setup(testPin, clockOutFunction);
  // setup clock output
  sysconPeripheral.setClockOutput(libmcull::syscon::clockOutSources::MAIN, 10u);
  // setup systick
  systickPeripheral.init(CLOCK_CPU / 2);
  systickPeripheral.start(systickIsrLambda);
  gpioPeripheral.output(ledPin);
}
