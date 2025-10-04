/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2025 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <minunit.h>

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
  minUnitPass(); // added to supress warnings
  testSetupExecuted = 123456789;
  return;
}

/**
 * \brief test testTeardown function
 */
MINUNIT_TEARDOWN(minunitTestTeardown)
{
  minUnitPass(); // added to supress warnings
  return;
}

/**
 * \brief Test setup and teardown functions
 */
MINUNIT_ADD(minunitTestSetupFunc, minunitTestSetup, minunitTestTeardown)
{
  minUnitCheck(testSetupExecuted == 123456789);
  // I cant see how to test teardown just yet
}

/**
 * \brief helper function to test automatic failure
 */
void TestBodyMinUnitFail(minunitState *testResults)
{
  minUnitFail();
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestmutestFail, NULL, NULL)
{
  minunitState localState;
  localState.executed = 0;
  localState.checks = 0;
  localState.failures = 0;
  localState.flagFailed = 0;
  TestBodyMinUnitFail(&localState);
  minUnitCheck(localState.executed == 0);
  minUnitCheck(localState.checks == 1);
  minUnitCheck(localState.failures == 0);
  minUnitCheck(localState.flagFailed == 1);
}

/**
 * \brief helper function to test passing mutest check
 */
void TestBodyMinUnitCheckFail(minunitState *testResults)
{
  minUnitCheck(1 == 0);
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestCheckFail, NULL, NULL)
{
  minunitState localState;
  localState.executed = 0;
  localState.checks = 0;
  localState.failures = 0;
  localState.flagFailed = 0;
  TestBodyMinUnitCheckFail(&localState);
  minUnitCheck(localState.executed == 0);
  minUnitCheck(localState.checks == 1);
  minUnitCheck(localState.failures == 0);
  minUnitCheck(localState.flagFailed == 1);
}

/**
 * \brief helper function to test passing mutest check
 */
void TestBodyMinUnitCheckPass(minunitState *testResults)
{
  minUnitCheck(1 == 1);
}

/**
 * \brief Test passing mutest check
 */
MINUNIT_ADD(minunitTestCheckPass, NULL, NULL)
{
  minunitState localState;
  localState.executed = 0;
  localState.checks = 0;
  localState.failures = 0;
  localState.flagFailed = 0;
  TestBodyMinUnitCheckPass(&localState);
  minUnitCheck(localState.executed == 0);
  minUnitCheck(localState.checks == 1);
  minUnitCheck(localState.failures == 0);
  minUnitCheck(localState.flagFailed == 0);
}