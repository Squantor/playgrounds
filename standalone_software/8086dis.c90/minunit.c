/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include "minunit.h"

MinunitState minunit_state;

void MinunitInit(void)
{
   minunit_state.failures = 0;
   minunit_state.checks = 0;
}
