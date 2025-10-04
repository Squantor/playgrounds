/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <minunit.h>

minunitTestsTable default_test_table = {0};

minunitState minunit_test_state;

void MinunitAddTest(minunitTestsTable *table, void (*testBody)(minunitState *testResults),
                    void (*testSetup)(minunitState *testResults), void (*testTeardown)(minunitState *testResults))
{
  if (table->testcount < MINUNIT_MAX_TESTS - 1)
  {
    table->tests[table->testcount].testBody = testBody;
    table->tests[table->testcount].testSetup = testSetup;
    table->tests[table->testcount].testTeardown = testTeardown;
    table->testcount++;
  }
}

int MinunitRun(void)
{
  return MinunitRunTableCallback(&default_test_table, NULL);
}

int MinunitRunCallback(intraTestCallback callback)
{
  return MinunitRunTableCallback(&default_test_table, callback);
}

int MinunitRunTableCallback(minunitTestsTable *table, intraTestCallback callback)
{
  minunit_test_state.executed = 0;
  minunit_test_state.failures = 0;
  minunit_test_state.checks = 0;
  for (int i = 0; i < table->testcount; i++)
  {
    if (table->tests[i].testSetup != NULL)
      table->tests[i].testSetup(&minunit_test_state);
    if (minunit_test_state.flagFailed == 0)
    {
      table->tests[i].testBody(&minunit_test_state);
      if (table->tests[i].testTeardown != NULL)
        table->tests[i].testTeardown(&minunit_test_state);
    }
    if (minunit_test_state.flagFailed != 0)
    {
      minunit_test_state.flagFailed = 0;
      minunit_test_state.failures++;
    }
    minunit_test_state.executed++;
    if (callback != NULL)
      callback();
#ifndef MINUNIT_REPORT_DISABLE
    MinunitReport("\n");
#endif
  }
  return 0;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

__attribute__((weak)) void MinunitReport(const char *message)
{
  // empty body, as this is a weak function, no action should be taken
}

__attribute__((weak)) void MinunitFailCallback() {}