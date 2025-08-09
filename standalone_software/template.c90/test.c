/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include "test.h"
#include <stdint.h>
#include <stdio.h>

int TestFunction(void)
{
   printf("Test function from %s %d\n", __FILE__, __LINE__);
   return 0;
}
