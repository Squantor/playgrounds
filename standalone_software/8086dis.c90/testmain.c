/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include "minunit.h"
#include <stdio.h>
#include "tests.h"

void MinunitReport(const char *message)
{
  printf("%s", message);
}

int main(int argc, char *argv[])
{
  (void)argc;
  (void)argv;
  MinunitInit();
  TestMovDisassembly();
  printf("%d checks, %d failed\n", minunit_state.checks, minunit_state.failures);
  return 0;
}
