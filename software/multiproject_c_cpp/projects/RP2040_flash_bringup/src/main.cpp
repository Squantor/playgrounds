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
#include <array>
#include <utility>
#include <cstddef>

constexpr size_t patternSize = 65536;

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

template <std::size_t Length, typename Generator>
constexpr auto lut(Generator&& f) {
  using content_type = decltype(f(std::size_t{0}));
  std::array<content_type, Length> arr{};
  for (std::size_t i = 0; i < Length; i++) {
    arr[i] = f(i);
  }
  return arr;
}

template <std::size_t Length>
inline constexpr auto patternTable = lut<Length>([](std::size_t n) {
  unsigned result = n;
  return result;
});

constinit const auto memoryTestTable = patternTable<patternSize>;

int main() {
  static uint32_t currTicks = 0;
  boardInit();
  while (1) {
    delay_cycles(10);
    __NOP();
    if (currTicks != systicks) {
      bool correct = true;
      for (size_t i = 0; i < patternSize; i++) {
        if (memoryTestTable[i] != i)
          correct = false;
      }
      if (correct != false)
        sioGpioOutXor(SIO, LED_MASK);
      currTicks = systicks;
    }
  }
}
