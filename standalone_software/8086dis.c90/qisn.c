/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Implementation of the instruction queue datastructure
*/
#include <string.h>
#include "qisn.h"


static u8 data[MAX_ISN_QUEUE_SIZE];
static u8 front;
static u8 back;

void QIReset(void)
{
    memset(data, 0, MAX_ISN_QUEUE_SIZE);
    front = 0;
    back = 0;
}

int QIFull(void)
{
    return 0;
}

int QIEmpty(void)
{
    return (front == back);
}


u8 QILevel()
{
    return 0;
}

