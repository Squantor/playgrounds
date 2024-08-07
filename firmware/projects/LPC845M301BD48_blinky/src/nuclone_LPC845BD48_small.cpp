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

libMcu::ll::iocon::iocon<libMcu::hw::ioconAddress> ioconPeripheral;
libMcu::ll::swm::swm<libMcu::hw::swmAddress> swmPeriperhal;
libMcu::ll::gpio::gpio<libMcu::hw::gpioAddress> gpioPeripheral;
libMcu::ll::syscon::syscon<libMcu::hw::sysconAddress> sysconPeripheral;
libMcu::ll::systick::systick<libMcu::hw::systickAddress> systickPeripheral;

auto systickIsrLambda = []() {
  gpioPeripheral.toggle(ledPin);
};

void boardInit(void) {
  // clock enables and resets
  sysconPeripheral.enablePeripheralClocks(
    libMcu::ll::syscon::peripheralClocks0::SWM | libMcu::ll::syscon::peripheralClocks0::IOCON |
      libMcu::ll::syscon::peripheralClocks0::GPIO0 | libMcu::ll::syscon::peripheralClocks0::GPIO1,
    0);
  // setup IOCON pins
  ioconPeripheral.setup(ledPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalInPin, libMcu::ll::iocon::pullModes::INACTIVE);
  ioconPeripheral.setup(xtalOutPin, libMcu::ll::iocon::pullModes::INACTIVE);
  swmPeriperhal.setup(xtalInPin, xtalInFunction);
  swmPeriperhal.setup(xtalOutPin, xtalOutFunction);
  // setup crystal oscillator
  sysconPeripheral.setSysOscControl(libMcu::hw::syscon::SYSOSCCTRL::NO_BYPASS | libMcu::hw::syscon::SYSOSCCTRL::FREQ_1_20MHz);
  sysconPeripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSOSC);
  libMcu::sw::delay(3000);
  // setup PLL
  sysconPeripheral.selectPllClock(libMcu::ll::syscon::pllClockSources::EXT);
  sysconPeripheral.depowerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  sysconPeripheral.setSystemPllControl(4, libMcu::ll::syscon::pllPostDivider::DIV_4);
  sysconPeripheral.powerPeripherals(libMcu::ll::syscon::powerOptions::SYSPLL);
  while (sysconPeripheral.getSystemPllStatus() == 0)
    ;
  sysconPeripheral.setSystemClockDivider(2);
  // switch mainclock
  // sysconPeripheral.selectMainClock(libMcu::ll::syscon::mainClockSources::EXT); // for selecting crystal oscillator
  sysconPeripheral.selectMainPllClock(libMcu::ll::syscon::mainClockPllSources::SYSPLL);
  // setup clock out test pin
  swmPeriperhal.setup(testPin, clockOutFunction);
  // setup clock output
  sysconPeripheral.setClockOutput(libMcu::ll::syscon::clockOutSources::MAIN, 10u);
  // setup systick
  systickPeripheral.init(CLOCK_CPU / 2);
  systickPeripheral.start(systickIsrLambda);
  gpioPeripheral.output(ledPin);
}
