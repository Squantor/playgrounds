/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/**
 * \file main.cpp
 * Main entrypoint for executing minunit tests
 */
#include <cstdio>
#include <minunit.h>

int failure_callbacks = 0;

/**
 * @brief reports message when a test fails
 * @param message failure message
 */
void MinunitReport(const char *message)
{
   printf("%s", message);
}

/**
 * @brief callback initiated when a test fails
 */
void MinunitFailCallback(void)
{
   failure_callbacks++;
}

/**
 * @brief main entrypoint
 * @return error code to operating system
 */
int main()
{
   MinunitRun();
   printf("%d tests executed\n", minunit_test_state.executed);
   printf("%d tests failed\n", minunit_test_state.failures);
   printf("%d checks executed\n", minunit_test_state.checks);
   return 0;
}
