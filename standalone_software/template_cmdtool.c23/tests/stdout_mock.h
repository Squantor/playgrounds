/**
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 *
 * @file stdout_mock.h
 * @brief Std output mock declarations used for unittests
 * @note This mock is implemented as a FIFO string queue
 */
#ifndef STDOUT_MOCK_H
#define STDOUT_MOCK_H

#define STDOUT_MOCK_BUFFER_SIZE 2048u  //! Mock buffer size

/**
 * @brief Initialize the stdout stub
 * @note All pointers returned will be invalidated
 */
void stdout_mock_init(void);

/**
 * @brief Write a string to mock buffer
 * @param str Pointer to the string to write
 */
void stdout_output(const char *str);

/**
 * @brief Write a string to mock buffer and add newline
 * @param str Pointer to the string to write
 */
void stdout_output_line(const char *str);

/* Get the last log output from buffer */
/**
 * @brief Get the first string from the mock buffer
 * @note The string is removed from the buffer
 * @note pointer returned is invalid after an init
 * @return Pointer to the string in the mock buffer
 */
const char *stdout_mock_get(void);

/**
 * @brief Check if the mock buffer is empty
 * @return 1 if empty, 0 if not
 */
int stdout_mock_is_empty(void);

#endif
