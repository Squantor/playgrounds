/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <minunit.h>
#include <stddef.h>

/**
 * \file minunitTests.cpp
 * Tests to execute minunit test functionality
 */

int testSetupExecuted;

/**
 * \brief test testSetup function
 */
MINUNIT_SETUP(minunitTestSetup)
{
   MINUNIT_PASS();  // added to supress warnings
   testSetupExecuted = 123456789;
   return;
}

/**
 * \brief test testTeardown function
 */
MINUNIT_TEARDOWN(minunitTestTeardown)
{
   MINUNIT_PASS();  // added to supress warnings
   return;
}

/**
 * \brief Test setup and teardown functions
 */
MINUNIT_ADD(minunitTestSetupFunc, minunitTestSetup, minunitTestTeardown)
{
   MINUNIT_CHECK(testSetupExecuted == 123456789);
   // I cant see how to test teardown just yet
}

/**
 * \brief helper function to test automatic failure
 */
void TestBodyMinUnitFail(MinunitState *test_results)
{
   MINUNIT_FAIL();
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestmutestFail, NULL, NULL)
{
   MinunitState local_state;
   local_state.executed = 0;
   local_state.checks = 0;
   local_state.failures = 0;
   local_state.flag_fail = 0;
   TestBodyMinUnitFail(&local_state);
   MINUNIT_CHECK(local_state.executed == 0);
   MINUNIT_CHECK(local_state.checks == 1);
   MINUNIT_CHECK(local_state.failures == 0);
   MINUNIT_CHECK(local_state.flag_fail == 1);
}

/**
 * \brief helper function to test passing mutest check
 */
void TestBodyMinUnitCheckFail(MinunitState *test_results)
{
   MINUNIT_CHECK(1 == 0);
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestCheckFail, NULL, NULL)
{
   MinunitState local_state;
   local_state.executed = 0;
   local_state.checks = 0;
   local_state.failures = 0;
   local_state.flag_fail = 0;
   TestBodyMinUnitCheckFail(&local_state);
   MINUNIT_CHECK(local_state.executed == 0);
   MINUNIT_CHECK(local_state.checks == 1);
   MINUNIT_CHECK(local_state.failures == 0);
   MINUNIT_CHECK(local_state.flag_fail == 1);
}

/**
 * \brief helper function to test passing mutest check
 */
void TestBodyMinUnitCheckPass(MinunitState *test_results)
{
   MINUNIT_CHECK(1 == 1);
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestCheckPass, NULL, NULL)
{
   MinunitState local_state;
   local_state.executed = 0;
   local_state.checks = 0;
   local_state.failures = 0;
   local_state.flag_fail = 0;
   TestBodyMinUnitCheckPass(&local_state);
   MINUNIT_CHECK(local_state.executed == 0);
   MINUNIT_CHECK(local_state.checks == 1);
   MINUNIT_CHECK(local_state.failures == 0);
   MINUNIT_CHECK(local_state.flag_fail == 0);
}
