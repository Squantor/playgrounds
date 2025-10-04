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
   // check test state
   if (minunit_test_state.executed != 5) {
      printf("incorrect number of tests executed\n");
   } else if (minunit_test_state.checks != 15) {
      printf("incorrect number of checks executed\n");
   } else if (minunit_test_state.failures != 0) {
      printf("Tests that have failed\n");
   } else if (failure_callbacks != 2) {
      printf("Incorrect number of failure callbacks \n");
   } else {
      printf("minunit tests passed\n");
   }
   return 0;
}