/**
 * @file main.cpp
 * @brief Main entry point file
 * 
 */

/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <test.h>
#include <stdio.h>
#include <iostream>

/**
 * @brief Main entry point function
 * 
 * @param argc argument count
 * @param argv argument list
 * @return int return code to return to callee
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  testfunc();
  printf("Hello World!\n");
  return 0;
}
