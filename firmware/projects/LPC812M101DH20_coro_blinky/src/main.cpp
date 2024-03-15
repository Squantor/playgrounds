/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <board.hpp>
#include <application.hpp>

int main() {
  boardInit();
  applicationLoop();
}
