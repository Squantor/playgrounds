/*
SPDX-License-Identifier: MIT

Copyright (c) 2025 Bart Bilos
For conditions of distribution and use, see LICENSE file
*/
#include <stdio.h>
#include <sqtypes.h>
#include <sqresult.h>

typedef enum
{
  kCmdOpt,  /* Command like "command option" */
  kOptOpt,  /* Option like "command -o" */
  kLongOpt, /* Long form option like "command --option" */
} CmdlineOpts;

/* Parsing tokens are also indices into CmdlineTbl */
typedef enum
{
  kCmdFoo = 0,
  kCmdBar,
  kCmdBaz,
  kOptA,
  kOptC,
  kParseTokCnt,
} CmdlineToks;

typedef struct
{
  CmdlineOpts type;
  s8 name;
} CmdlineElem;

CmdlineElem CmdlineTbl[kParseTokCnt] = {
    {kCmdOpt, s8("foo")},
    {kCmdOpt, s8("bar")},
    {kCmdOpt, s8("baz")},
    {kOptOpt, s8("a")},
    {kOptOpt, s8("c")},
};

results ParseOption(char c)
{
  size i;
  // loop through array to find the option
  for (i = 0; i < kParseTokCnt; i++)
  {
    if (CmdlineTbl[i].type == kOptOpt && CmdlineTbl[i].name.data[0] == c)
    {
      // add token to token array
      return kResOk;
    }
  }
  return kResOk;
}

results ParseOptions(int argc, char *argv[])
{
  int i;

  for (i = 1; i < argc; i++)
  {
    /* does the argument start with -*/
    if (argv[i][0] == '-')
    {
    }
    /* cut it off and parse the single character optiosn */
    /* does the argument start with an alphanumeric char? */
    /* parse it as a command */
  }

  return kResOk;
}

int main(int argc, char *argv[])
{
  int i;
  printf("%d arguments\n", argc);
  for (i = 0; i < argc; i++)
    printf("%d: %s\n", i, argv[i]);
  return 0;
}
