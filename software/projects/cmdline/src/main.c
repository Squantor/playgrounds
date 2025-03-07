/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdio.h>

int main(int argc, char *argv[])
{
  int i;
  printf("%d arguments\n", argc);
  for (i = 0; i < argc; i++)
    printf("%d: %s\n", i, argv[i]);
  return 0;
}
