/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file log_out_stub.h
 * @brief Log output stub declarations used for unittests
 */
#ifndef LOG_OUT_STUB_H
#define LOG_OUT_STUB_H

/** Initialize log output stub */
void log_out_stub_init(void);

/* Write log output to stub buffer */
void log_output(const char *str);

/* Get log output from stub buffer */
char *log_out_stub_get(void);

#endif