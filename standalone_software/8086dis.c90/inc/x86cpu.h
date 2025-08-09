/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
X86 CPU state definitions
*/
#ifndef X86CPU_H
#define X86CPU_H

#include "types.h"

typedef struct {
   u16 ip; /* Instruction Pointer */
   u16 cs; /* Code Segment */
   u16 ss; /* Stack Segment */
   u16 ds; /* Data segment */
   u16 es; /* Extra segment */
   /* Any additional CPU state variables */
   /* Any more advanced cpu ifdefs here? */
} X86CpuState;

#endif
