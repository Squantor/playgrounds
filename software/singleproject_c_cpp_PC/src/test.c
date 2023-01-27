/**
 * @file test.c
 * @brief test C file
 * 
 */
/*
SPDX-License-Identifier: MIT

Copyright (c) 2021 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdint.h>
#include <stdio.h>
#include <test.h>

/**
 * @brief 
 * 
 * @return int 
 */
int testfunc(void)
{
    printf("Test function from %s %d\n", __FILE__, __LINE__);
    return 0;
}
