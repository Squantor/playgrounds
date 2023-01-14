/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2023 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/*
 * This is simple example file which does do any I/O and thus
 * can be compiled and run on any Cortex-M MCU. However, to see
 * its effect, you'll need to use debugger.
 */
#include <nuclone_RP2040.hpp>

volatile uint32_t systicks = 0;

extern "C" {
void SysTick_Handler(void) {
  systicks = systicks + 1;
}
}

__attribute__((noinline, section(".ramfunc"))) void delay_cycles(uint32_t cycles) {
  cycles /= 4;

  asm volatile(
    "1: sub %[cycles], %[cycles], #1 \n"
    "   nop \n"
    "   bne 1b \n"
    : [cycles] "+l"(cycles));
}

int main() {
  static uint32_t currTicks = 0;
  boardInit();
  while (1) {
    delay_cycles(10);
    __NOP();
    if (currTicks != systicks) {
      uint8_t dataWrite = (uint8_t)(currTicks & 0xFF);
      uartWriteBlocking(UART0, &dataWrite, sizeof(dataWrite));
      uint8_t dataRead = 0;
      uartReadBlocking(UART0, &dataRead, sizeof(dataRead));
      if (dataRead != dataWrite)
        __NOP();
      sioGpioOutXor(SIO, LED_MASK);
      currTicks = systicks;
    }
  }
}
