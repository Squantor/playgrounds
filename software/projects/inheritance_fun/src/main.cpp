/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/

#include <format>
#include <highest.hpp>
#include <iostream>

highest testDut;

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  testDut.doit();
  return 0;
}
