/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <cstdint>
#include <cstdio>

#define xstr(s) str(s)
#define str(s) #s

int main() {
  printf("test string %s\n", xstr(TEST));
  return 0;
}
