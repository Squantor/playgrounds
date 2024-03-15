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

std::array<char, 16> adcRawString{"ADC raw is: "};
std::array<char, 16> adcValueString{" ADC value is: "};
std::array<char, 3> crlfString{"\n\r"};
std::array<char, 64> uartOutputBuffer;

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
  std::uint32_t adcRaw;
  std::int32_t adcValue;
  CR_WAIT_V(testAdc.getSample(isMcp355XReady, disableMcp355X, adcRaw, adcValue) == libMcuLL::results::DONE);

  // construct output string
  std::span<char> output;
  output = uartOutputBuffer;
  output = util::appendString(output, adcRawString);
  output = util::appendHex(output, adcRaw);
  output = util::appendString(output, adcValueString);
  output = util::appendDec(output, adcValue);
  output = util::appendString(output, crlfString);
  // output Uart stuff
  CR_WAIT_V(mainUsartPeripheral.claim() == libMcuLL::results::CLAIMED);
  CR_WAIT_V(mainUsartPeripheral.startWrite(std::span(uartOutputBuffer.begin(), strlen(uartOutputBuffer.data()))) ==
            libMcuLL::results::STARTED);
  CR_WAIT_V(mainUsartPeripheral.progressWrite() == libMcuLL::results::DONE);
  CR_WAIT_V(mainUsartPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);

  CR_END_V();
}