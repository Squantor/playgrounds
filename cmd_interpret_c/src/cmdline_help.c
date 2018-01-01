#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmdline.h>
#include <results.h>
#include <cmdline_commands.h>

char strCmdHelpTrigger[] = "help";
char strHelpHelp[] = "help - shows help information on all commands";

result CmdHelpHandler(int * arglist)
{
    int i = 0;
    while(cmdLineEntries[i].strHelp != NULL)
    {
        printf("%s\n", cmdLineEntries[i].strHelp);
        i++;
    }
    return noError;
}
