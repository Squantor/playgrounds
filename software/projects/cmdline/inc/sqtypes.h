/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
/*
Trying to emulate Chris Wellons coding style a bit in C
https://nullprogram.com/blog/2023/10/08/
*/
#ifndef SQTYPES_H
#define SQTYPES_H

typedef unsigned char u8;       /* byte sized unsigned integer */
typedef unsigned char b8;       /* byte sized boolean */
typedef signed char i8;         /* byte sized signed integer */
typedef unsigned short int u16; /* word sized unsigned integer */
typedef signed short int i16;   /* word sized signed integer */
typedef int i32;                /* doubleword sized signed integer */
typedef unsigned int u32;       /* doubleword sized unsigned integer */
typedef char byte;              /* byte sized signed integer */
typedef size_t size;            /* size */

#define countof(a) (size)(sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)
#define new(a, t, n) (t *)alloc(a, sizeof(t), _Alignof(t), n)

/* Example forward declaration */
/*
typedef struct map map;
struct map
{
  map *child[4];
};
*/

#define s8(s) \
  (s8) { (u8 *)s, lengthof(s) }
typedef struct
{
  u8 *data;
  size len;
} s8;

#endif