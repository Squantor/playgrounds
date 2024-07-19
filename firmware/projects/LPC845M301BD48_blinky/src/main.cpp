/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2024 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief blinking LED demo project
 */
#include <nuclone_LPC845BD48_small.hpp>

extern "C" {
void SysTick_Handler(void) {
  systickPeripheral.isr();
}
}

int main() {
  boardInit();
  while (1) {
  }
}
