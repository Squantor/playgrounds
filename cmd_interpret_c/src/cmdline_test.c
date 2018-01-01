#include <stdint.h>
#include <stdio.h>
#include <cmdline.h>
#include <results.h>

char strCmdTestTrigger[] = "test";
char strTestHelp[] = "test - Basic test command, accepts two arguments";

result CmdTestHandler(int * arglist)
{
    printf("test arguments are %d and %d\n", arglist[0], arglist[1]);
    return noError;
}