/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <measure.hpp>
#include <string.h>
#include <span>
#include <format.hpp>

std::array<char, 16> promptString{"ADC value is: "};
std::array<char, 3> crlfString{"\n\r"};
std::array<char, 32> uartOutputBuffer;
std::array<std::uint16_t, 2> adcSampleOutput;

uint32_t conversionReady(void) {
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
  CR_WAIT_V(mainSpiPeripheral.startRead(libMcuLL::sw::spi::chipEnables::SSEL_NONE, adcSampleOutput, 24, false) ==
            libMcuLL::results::STARTED);
  while (mainSpiPeripheral.progress() != libMcuLL::results::DONE)
    ;
  gpioPeripheral.high(adcSpiCePin);
  CR_WAIT_V(mainSpiPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);
  // Start a new conversion of the MCP3551
  crudeDelay(15);  // wait until MCP3551s internal state is normalized
  conversionReady();
  // construct output string
  std::span<char> output;
  output = uartOutputBuffer;
  output = util::appendString(output, promptString);
  output = util::appendHex(output, adcSampleOutput[0]);
  output = util::appendHex(output, static_cast<uint8_t>(adcSampleOutput[1]));
  output = util::appendString(output, crlfString);
  // output Uart stuff
  CR_WAIT_V(mainUsartPeripheral.claim() == libMcuLL::results::CLAIMED);
  CR_WAIT_V(mainUsartPeripheral.startWrite(std::span(uartOutputBuffer.begin(), strlen(uartOutputBuffer.data()))) ==
            libMcuLL::results::STARTED);
  CR_WAIT_V(mainUsartPeripheral.progressWrite() == libMcuLL::results::DONE);
  CR_WAIT_V(mainUsartPeripheral.unclaim() == libMcuLL::results::UNCLAIMED);

  CR_END_V();
}