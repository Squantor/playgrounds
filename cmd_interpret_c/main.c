#include <stdio.h>
#include <stdlib.h>
#include "results.h"
#include "cmdline.h"

char strHelpTest[] = "help\n";
char strTestTest[] = "test 1 2";

int main()
{
    // feed a command to the interpeter
    if(cmdlineParse(strHelpTest) == noError)
    {
        printf("Test help command passed\n");
    }
    // did we get a match?
    return 0;
}
