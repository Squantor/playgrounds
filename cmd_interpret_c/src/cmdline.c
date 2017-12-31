#include <string.h>
#include <stdio.h>

#include "results.h"
#include "cmdline.h"
#include "cmdline_commands.h"

result cmdlineParse(char * line)
{
    char commandline[64];
    strncpy(commandline, line, sizeof(commandline));
    char *trigger = strtok(commandline,STRTOK_DELIM);
    // match to the command table
    for(int i; cmdLineEntries[i].strTrigger != NULL; i++)
    {
        printf("matching %s with %s\n", trigger, cmdLineEntries[i].strTrigger);
    }
    // no match, return error;
    // parse arguments
    // matches the expected count?
    // call the callee with the argument count
    return noError;
}

