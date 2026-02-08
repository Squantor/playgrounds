/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file main.cpp
 * Main entrypoint for executing minunit tests
 */
#include <minunit.h>
#include <stdio.h>

int failure_callbacks = 0;

/**
 * @brief reports message when a test fails
 * @param message failure message
 */
void minunit_report(const char *message)
{
  printf("%s", message);
}

/**
 * @brief callback initiated when a test fails
 */
void minunit_fail_callback(void)
{
  failure_callbacks++;
}

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main()
{
  minunit_run();
  printf("tests executed: %u\n", minunit_test_state.executed);
  printf("checks executed: %u\n", minunit_test_state.checks);
  printf("failures: %u\n", minunit_test_state.failures);
  return 0;
}
