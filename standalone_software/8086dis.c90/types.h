/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
8086 disassembler types
*/
#ifndef TYPES_H
#define TYPES_H

/* basic types */
typedef unsigned char u8;
typedef unsigned short int u16;
typedef signed short int i16;
typedef signed int b32;
typedef signed int i32;
typedef unsigned int u32;
typedef float f32;
typedef double f64;
typedef unsigned long int uptr;
typedef char byte;
typedef long unsigned int usize;

/* Entry in the instruction table to handle an instruction */
typedef struct 
{
    u8 isn; /* Instruction byte */
    u8 isn_mask; /* Instruction byte mask */
    /* function pointer to handler */
} ByteHandler;


#endif