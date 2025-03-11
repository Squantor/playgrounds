/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#ifndef MINUNIT_H
#define MINUNIT_H

/* Helper to convert a macro literal to a string */
#define STRINGIFY(x) #x
/* Converts a macro literal to a string */
#define TOSTRING(x) STRINGIFY(x)
/* Helper macro for function style macros */
#define MU__SAFE_BLOCK(block) \
  do                          \
  {                           \
    block                     \
  } while (0)

/* Assert test macro, stops the test when the check fails */
#define MinunitAssert(test)                                                                  \
  MU__SAFE_BLOCK(                                                                            \
      minunit_state.checks++; if (!(test)) {                                                 \
        MinunitReport("\n" __FILE__ ":" TOSTRING(__LINE__) " failed: " TOSTRING(test) "\n"); \
        return;                                                                              \
      } else { MinunitReport("."); })

/* Expect test macro, does not stop the test when the check fails */
#define MinunitExpect(test)                                                                  \
  MU__SAFE_BLOCK(                                                                            \
      minunit_state.checks++; if (!(test)) {                                                 \
        MinunitReport("\n" __FILE__ ":" TOSTRING(__LINE__) " failed: " TOSTRING(test) "\n"); \
        return;                                                                              \
      } else { MinunitReport("."); })

/* Defines a test */
#define MINUNIT_TEST(name) static void minunit_##name(void)

/* minunitState is used to track the state of the test suite. */
typedef struct
{
  int executed; /*!< Total tests executed */
  int failures; /*!< Total asserts failed */
  int checks;   /*!< Total test asserts executed */
} MinunitState;

/* minunit state */
extern MinunitState minunit_state;
/* reporting function for minunit */
extern void MinunitReport(const char *message);
/* initialize minunit */
void MinunitInit(void);

#endif