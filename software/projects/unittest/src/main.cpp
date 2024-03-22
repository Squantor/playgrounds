/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <cstdio>
#include <iostream>
#include <test_project.hpp>
#include <unittest.hpp>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  RegisterTest(module, test1);
  RegisterTest(module, test2);

  RunTests();

  return 0;
}
