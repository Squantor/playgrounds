/*
SPDX-License-Identifier: MIT

Copyright (c) 2024 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <cstdint>
#include <cstdio>

// Macro for adding quotes
#define STRINGIFY(X) STRINGIFY2(X)
#define STRINGIFY2(X) #X

// Macros for concatenating tokens
#define CAT(X, Y) CAT2(X, Y)
#define CAT2(X, Y) X##Y
#define CAT_2 CAT
#define CAT_3(X, Y, Z) CAT(X, CAT(Y, Z))
#define CAT_4(A, X, Y, Z) CAT(A, CAT_3(X, Y, Z))

#define INCLUDE_FILE(ARGUMENT) STRINGIFY(CAT_3(ARGUMENT, ., hpp))

int main() {
  printf("test string %s\n", STRINGIFY(INCLUDE_FILE(broccoli)));
  return 0;
}
