/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <measure.hpp>
#include <string.h>

char testString[] = "Hello output\n";
std::array<std::uint16_t, sizeof(testString)> testOutput;
std::array<std::uint16_t, 2> adcSampleOutput;

uint32_t conversionReady(void) {
  // preset GPIO's
  gpioPeripheral.input(mainSpiMisoPin);
  gpioPeripheral.output(mainSpiSckPin);
  gpioPeripheral.low(mainSpiSckPin);
  gpioPeripheral.output(adcSpiCePin);
  gpioPeripheral.high(adcSpiCePin);
  // switch pins to GPIO
  swmPeriperhal.clear(mainSpiMisoPin, mainSpiMisoFunction);
  swmPeriperhal.clear(mainSpiSckPin, mainSpiSckFunction);
  swmPeriperhal.clear(adcSpiCePin, adcSpiCeFunction);
  // Chip enable
  gpioPeripheral.low(adcSpiCePin);
  // keep low for a while to start next conversion
  crudeDelay(10);
  uint32_t state = gpioPeripheral.get(mainSpiMisoPin);
  // Chip disable
  gpioPeripheral.high(adcSpiCePin);
  // switch pins to SPI
  swmPeriperhal.setup(mainSpiMisoPin, mainSpiMisoFunction);
  swmPeriperhal.setup(mainSpiSckPin, mainSpiSckFunction);
  swmPeriperhal.setup(adcSpiCePin, adcSpiCeFunction);
  return state;
}

void measure::execute(void) {
  CR_BEGIN(crCurrent);
  // CR_WAIT_V(currSystick != sysTick);
  // currSystick = sysTick;

  // sense if a sample is ready
  CR_WAIT_V(conversionReady() == 0);
  adcSampleOutput[0] = 0xDEAD;
  adcSampleOutput[1] = 0xBEEF;
  // do SPI stuff
  CR_WAIT_V(mainSpiPeripheral.claim() == libMcuLL::results::CLAIMED);
  CR_WAIT_V(mainSpiPeripheral.startRead(adcChipEnable, adcSampleOutput, 24, true) == libMcuLL::results::STARTED);
  CR_WAIT_V(mainSpiPeripheral.progress() == libMcuLL::results::DONE);
  CR_WAIT_V(mainSpiPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
  // output Uart stuff
  char *p = testString;
  for (std::uint16_t &data : testOutput) {
    data = *p;
    p++;
  }
  CR_WAIT_V(mainUsartPeripheral.claim() == libMcuLL::results::CLAIMED);
  CR_WAIT_V(mainUsartPeripheral.startWrite(testOutput) == libMcuLL::results::STARTED);
  CR_WAIT_V(mainUsartPeripheral.progressWrite() == libMcuLL::results::DONE);
  CR_WAIT_V(mainUsartPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
  // Start a new conversion of the MCP3551
  __NOP();
  conversionReady();
  CR_END_V();
}