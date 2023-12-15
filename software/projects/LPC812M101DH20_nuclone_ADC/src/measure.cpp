/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <measure.hpp>
#include <string.h>
#include <span>
#include <format.hpp>
#include <MCP355X.hpp>

std::array<char, 16> promptString{"ADC value is: "};
std::array<char, 3> crlfString{"\n\r"};
std::array<char, 32> uartOutputBuffer;
uint32_t adcSampleOutput;

driverMCP355X testAdc(mainSpiPeripheral);

auto isMcp355XReady = [](void) {
  // preset GPIO's
  gpioPeripheral.output(adcSpiCePin);
  gpioPeripheral.high(adcSpiCePin);
  // Chip enable
  gpioPeripheral.low(adcSpiCePin);
  // keep low for a while to start next conversion
  crudeDelay(15);
  uint32_t state = gpioPeripheral.get(mainSpiMisoPin);
  // Chip disable
  if (state != 0) {
    gpioPeripheral.high(adcSpiCePin);
  }
  return state != 0;
};

auto disableMcp355X = [](void) {
  gpioPeripheral.high(adcSpiCePin);
};

void measure::execute(void) {
  CR_BEGIN(crCurrent);
  // CR_WAIT_V(currSystick != sysTick);
  // currSystick = sysTick;

  // do SPI stuff
  CR_WAIT_V(testAdc.getSample(isMcp355XReady, disableMcp355X, adcSampleOutput) == libMcuLL::results::DONE);

  // construct output string
  std::span<char> output;
  output = uartOutputBuffer;
  output = util::appendString(output, promptString);
  output = util::appendHex(output, adcSampleOutput);
  output = util::appendString(output, crlfString);
  // output Uart stuff
  CR_WAIT_V(mainUsartPeripheral.claim() == libMcuLL::results::CLAIMED);
  CR_WAIT_V(mainUsartPeripheral.startWrite(std::span(uartOutputBuffer.begin(), strlen(uartOutputBuffer.data()))) ==
            libMcuLL::results::STARTED);
  CR_WAIT_V(mainUsartPeripheral.progressWrite() == libMcuLL::results::DONE);
  CR_WAIT_V(mainUsartPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);

  CR_END_V();
}