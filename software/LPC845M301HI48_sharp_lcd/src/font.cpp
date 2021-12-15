/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
#include <font.hpp>

const uint16_t ascii2font8x8[] = {
    0,  // U+0000 (null)
    0,  // U+0001 (SOH)
    0,  // U+0002 (STX)
    0,  // U+0003 (ETX)
    0,  // U+0004 (EOT)
    0,  // U+0005 (ENQ)
    0,  // U+0006 (ACK)
    0,  // U+0007 (BEL)
    0,  // U+0008 (BS)
    0,  // U+0009 (TAB)
    0,  // U+000A (LF)
    0,  // U+000B (VT)
    0,  // U+000C (FF)
    0,  // U+000D (CR)
    0,  // U+000E (SO)
    0,  // U+000F (SI)
    0,  // U+0010 (DLE)
    0,  // U+0011 (DC1)
    0,  // U+0012 (DC2)
    0,  // U+0013 (DC3)
    0,  // U+0014 (DC4)
    0,  // U+0015 (NAK)
    0,  // U+0016 (SYN)
    0,  // U+0017 (ETB)
    0,  // U+0018 (CAN)
    0,  // U+0019 (EM)
    0,  // U+001A (SUB)
    0,  // U+001B (ESC)
    0,  // U+001C (FS)
    0,  // U+001D (GS)
    0,  // U+001E (RS)
    0,  // U+001F (US)
    0,  // U+0020 (Space)
    8,  // U+0021 (!)
    16,  // U+0022 (")
    24,  // U+0023 (#)
    32,  // U+0024 ($)
    40,  // U+0025 (%)
    48,  // U+0026 (&)
    56,  // U+0027 (')
    64,  // U+0028 (()
    72,  // U+0029 ())
    80,  // U+002A (*)
    88,  // U+002B (+)
    96,  // U+002C (,)
    104,  // U+002D (-)
    112,  // U+002E (.)
    120,  // U+002F (/)
    128,  // U+0030 (0)
    136,  // U+0031 (1)
    144,  // U+0032 (2)
    152,  // U+0033 (3)
    160,  // U+0034 (4)
    168,  // U+0035 (5)
    176,  // U+0036 (6)
    184,  // U+0037 (7)
    192,  // U+0038 (8)
    200,  // U+0039 (9)
    208,  // U+003A (:)
    216,  // U+003B (;)
    224,  // U+003C (<)
    232,  // U+003D (=)
    240,  // U+003E (>)
    248,  // U+003F (?)
    256,  // U+0040 (@)
    264,  // U+0041 (A)
    272,  // U+0042 (B)
    280,  // U+0043 (C)
    288,  // U+0044 (D)
    296,  // U+0045 (E)
    304,  // U+0046 (F)
    312,  // U+0047 (G)
    320,  // U+0048 (H)
    328,  // U+0049 (I)
    336,  // U+004A (J)
    344,  // U+004B (K)
    352,  // U+004C (L)
    360,  // U+004D (M)
    368,  // U+004E (N)
    376,  // U+004F (O)
    384,  // U+0050 (P)
    392,  // U+0051 (Q)
    400,  // U+0052 (R)
    408,  // U+0053 (S)
    416,  // U+0054 (T)
    424,  // U+0055 (U)
    432,  // U+0056 (V)
    440,  // U+0057 (W)
    448,  // U+0058 (X)
    456,  // U+0059 (Y)
    464,  // U+005A (Z)
    472,  // U+005B ([)
    480,  // U+005C (\)
    488,  // U+005D (])
    496,  // U+005E (^)
    504,  // U+005F (_)
    512,  // U+0060 (`)
    520,  // U+0061 (a)
    528,  // U+0062 (b)
    536,  // U+0063 (c)
    544,  // U+0064 (d)
    552,  // U+0065 (e)
    560,  // U+0066 (f)
    568,  // U+0067 (g)
    576,  // U+0068 (h)
    584,  // U+0069 (i)
    592,  // U+006A (j)
    600,  // U+006B (k)
    608,  // U+006C (l)
    616,  // U+006D (m)
    624,  // U+006E (n)
    632,  // U+006F (o)
    640,  // U+0070 (p)
    648,  // U+0071 (q)
    656,  // U+0072 (r)
    664,  // U+0073 (s)
    672,  // U+0074 (t)
    680,  // U+0075 (u)
    688,  // U+0076 (v)
    696,  // U+0077 (w)
    704,  // U+0078 (x)
    712,  // U+0079 (y)
    720,  // U+007A (z)
    728,  // U+007B (})
    736,  // U+007C (|)
    744,  // U+007D (})
    752,  // U+007E (~)
    0,  // U+007F (DEL)
};

const uint8_t font8x8[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0020 (space)
    0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00, // U+0021 (!)
    0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0022 (")
    0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00, // U+0023 (#)
    0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00, // U+0024 ($)
    0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00, // U+0025 (%)
    0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00, // U+0026 (&)
    0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0027 (')
    0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00, // U+0028 (()
    0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00, // U+0029 ())
    0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00, // U+002A (*)
    0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00, // U+002B (+)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06, // U+002C (,)
    0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, // U+002D (-)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00, // U+002E (.)
    0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00, // U+002F (/)
    0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00, // U+0030 (0)
    0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00, // U+0031 (1)
    0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00, // U+0032 (2)
    0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00, // U+0033 (3)
    0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00, // U+0034 (4)
    0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00, // U+0035 (5)
    0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00, // U+0036 (6)
    0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00, // U+0037 (7)
    0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00, // U+0038 (8)
    0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00, // U+0039 (9)
    0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00, // U+003A (:)
    0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06, // U+003B (;)
    0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00, // U+003C (<)
    0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00, // U+003D (=)
    0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00, // U+003E (>)
    0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00, // U+003F (?)
    0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00, // U+0040 (@)
    0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00, // U+0041 (A)
    0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00, // U+0042 (B)
    0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00, // U+0043 (C)
    0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00, // U+0044 (D)
    0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00, // U+0045 (E)
    0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00, // U+0046 (F)
    0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00, // U+0047 (G)
    0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00, // U+0048 (H)
    0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, // U+0049 (I)
    0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00, // U+004A (J)
    0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00, // U+004B (K)
    0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00, // U+004C (L)
    0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00, // U+004D (M)
    0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00, // U+004E (N)
    0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00, // U+004F (O)
    0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00, // U+0050 (P)
    0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00, // U+0051 (Q)
    0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00, // U+0052 (R)
    0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00, // U+0053 (S)
    0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, // U+0054 (T)
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00, // U+0055 (U)
    0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00, // U+0056 (V)
    0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00, // U+0057 (W)
    0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00, // U+0058 (X)
    0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00, // U+0059 (Y)
    0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00, // U+005A (Z)
    0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00, // U+005B ([)
    0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00, // U+005C (\)
    0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00, // U+005D (])
    0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, // U+005E (^)
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, // U+005F (_)
    0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, // U+0060 (`)
    0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00, // U+0061 (a)
    0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00, // U+0062 (b)
    0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00, // U+0063 (c)
    0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00, // U+0064 (d)
    0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00, // U+0065 (e)
    0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00, // U+0066 (f)
    0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F, // U+0067 (g)
    0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00, // U+0068 (h)
    0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, // U+0069 (i)
    0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, // U+006A (j)
    0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00, // U+006B (k)
    0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00, // U+006C (l)
    0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00, // U+006D (m)
    0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00, // U+006E (n)
    0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00, // U+006F (o)
    0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F, // U+0070 (p)
    0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78, // U+0071 (q)
    0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00, // U+0072 (r)
    0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00, // U+0073 (s)
    0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00, // U+0074 (t)
    0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00, // U+0075 (u)
    0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00, // U+0076 (v)
    0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00, // U+0077 (w)
    0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00, // U+0078 (x)
    0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F, // U+0079 (y)
    0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00, // U+007A (z)
    0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00, // U+007B ({)
    0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00, // U+007C (|)
    0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00, // U+007D (})
    0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // U+007E (~)
};