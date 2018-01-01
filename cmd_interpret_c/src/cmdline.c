#include <string.h>
#include <stdio.h>

#include "results.h"
#include "cmdline.h"
#include "cmdline_commands.h"

result cmdlineParseInt(char * token, int * value)
{
    return noError;
}

result cmdlineParseHex(char * token, int * value)
{
    return noError;
}

result cmdlineParseArg(char * token, int * value)
{
    int tokLen = strlen(token);
    // if the token is smaller then 3 then it is not hex
    if(tokLen > 2)
    {
        if((token[0] == '0') && (token[1] == 'x'))
        {
            return cmdlineParseHex(token, value);
        }
    }
    // not hex, fall through to int parsing
    return cmdlineParseInt(token, value);
}

result cmdlineParse(char * line)
{
    char commandline[CMDLINE_MAX_LENGTH];
    strncpy(commandline, line, sizeof(commandline));
    char *trigger = strtok(commandline,STRTOK_DELIM);
    // match to the command table
    for(int i = 0; cmdLineEntries[i].strTrigger != NULL; i++)
    {
        if(strcmp(trigger, cmdLineEntries[i].strTrigger) == 0)
        {
            // matched, parse arguments of commandline
            for(int j = 0; j < cmdLineEntries[i].argCnt; j++)
            {
                int arguments[CMDLINE_MAX_ARGS];
                char *arg = strtok(commandline,STRTOK_DELIM);
                if(arg == NULL)
                    return cmdlineInvalidArg;
                result argparse = cmdlineParseArg(arg, &arguments[j]);
                if(argparse != noError)
                    return argparse;
            }
            // call the matched command with the argument count
            return noError;
        }
    }
    return cmdlineNotFound;
}

