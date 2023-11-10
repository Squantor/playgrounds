/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <measure.hpp>
#include <string.h>

char testString[] = "Hello output\n";
std::array<std::uint16_t, sizeof(testString)> testOutput;

void measure::execute(void) {
  CR_BEGIN(crCurrent);
  CR_WAIT_V(currSystick != sysTick);
  currSystick = sysTick;
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
  CR_END_V();
}