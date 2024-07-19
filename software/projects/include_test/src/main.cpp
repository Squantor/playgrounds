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
#define CAT_3(X, Y, Z) CAT_2(X, CAT_2(Y, Z))
#define CAT_4(A, X, Y, Z) CAT_2(A, CAT_3(X, Y, Z))

#define APP_STRING()

#define INCLUDE_FILE(ARGUMENT) STRINGIFY(CAT_2(ARGUMENT, _m.hpp))

// #if __has_include("sub/broccoli_m.hpp")
#include INCLUDE_FILE(DEVICE)
/*#else
#error "unknown include"
#endif*/

int main() {
  // printf("test string %s\n", DEVICE_TYPE);
  printf("include file string %s\n", INCLUDE_FILE(DEVICE));
  return 0;
}
