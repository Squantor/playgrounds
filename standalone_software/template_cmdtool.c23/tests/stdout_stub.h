/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file stdout_stub.h
 * @brief Std output stub declarations used for unittests
 */
#ifndef STDOUT_STUB_H
#define STDOUT_STUB_H

/** Initialize log output stub */
void stdout_stub_init(void);

/* Write log output to stub buffer */
void stdout_output(const char *str);

/* Get log output from stub buffer */
char *stdout_stub_get(void);

#endif