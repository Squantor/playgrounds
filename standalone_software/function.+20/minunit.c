/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * \file minunit.c
 * Minimal C++ unittesting framework code
 */
#include <minunit.h>
#include <stddef.h>

MinunitTestsTable default_test_table = {0};

MinunitState minunit_test_state;

void MinunitAddTest(MinunitTestsTable *table,
                    void (*body)(MinunitState *test_results),
                    void (*setup)(MinunitState *test_results),
                    void (*teardown)(MinunitState *test_results))
{
   if (table->testcount < MINUNIT_MAX_TESTS - 1) {
      table->tests[table->testcount].body = body;
      table->tests[table->testcount].setup = setup;
      table->tests[table->testcount].teardown = teardown;
      table->testcount++;
   }
}

int MinunitRun(void)
{
   return MinunitRunTableCallback(&default_test_table, NULL);
}

int MinunitRunCallback(IntraTestCallback callback)
{
   return MinunitRunTableCallback(&default_test_table, callback);
}

int MinunitRunTableCallback(MinunitTestsTable *table,
                            IntraTestCallback callback)
{
   minunit_test_state.executed = 0;
   minunit_test_state.failures = 0;
   minunit_test_state.checks = 0;
   for (int i = 0; i < table->testcount; i++) {
      if (table->tests[i].setup != NULL)
         table->tests[i].setup(&minunit_test_state);
      if (minunit_test_state.flag_fail == 0) {
         table->tests[i].body(&minunit_test_state);
         if (table->tests[i].teardown != NULL)
            table->tests[i].teardown(&minunit_test_state);
      }
      if (minunit_test_state.flag_fail != 0) {
         minunit_test_state.flag_fail = 0;
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

__attribute__((weak)) void MinunitFailCallback()
{
}
