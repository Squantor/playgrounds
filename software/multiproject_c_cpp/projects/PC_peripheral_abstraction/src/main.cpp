/*
SPDX-License-Identifier: MIT

Copyright (c) 2023 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file main.cpp
 *
 * Main program entry point
 *
 * Program execution starts here in main().
 */
#include <cstdio>
#include <MinUnit.h>
#include <board.hpp>

/** \brief overridden reporting function
 *
 * Executes the minunit test framework and checks the results
 */
void minunitReport(const char *message) {
  printf("%s", message);
}

/**
 * \brief Program entry point
 *
 * Program entry point, execution starts here. Any unittest initialisation happens here.
 *
 * \return returns the error code to the operating system
 */
int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;
  minunitRun();
  printf("Tests run: %d\n", minunitTestState.executed);
  printf("Tests failed: %d\n", minunitTestState.failures);
  printf("Checks executed: %d\n", minunitTestState.checks);
  if (minunitTestState.failures == 0)
    return 0;
  else
    return -1;
}
