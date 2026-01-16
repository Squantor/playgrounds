/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @brief main entry point for SH1106 test project
 */
#include <LPC845QFP48_UI_SH1106_5btn.hpp>
#include <application.hpp>

Application controller;

int main() {
  BoardInit();
  controller.Init();
  while (1) {
    controller.Progress();
    event_dispatcher.Process();
    BoardProgress();
  }
}