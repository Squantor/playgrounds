#include <string.h>
#include <stdio.h>

#include "results.h"
#include "cmdline.h"
#include "cmdline_commands.h"

result cmdlineParseInt(char * token, int * value)
{
    int tokenLength = strlen(token);
    int multiplier = 1;
    int i = tokenLength;
    int parsedValue = 0;
    while(i != 0)
    {
        i--;
        switch(token[i])
        {
            case '0':  break;
            case '1': parsedValue = parsedValue + (1 * multiplier); break;
            case '2': parsedValue = parsedValue + (2 * multiplier); break;
            case '3': parsedValue = parsedValue + (3 * multiplier); break;
            case '4': parsedValue = parsedValue + (4 * multiplier); break;
            case '5': parsedValue = parsedValue + (5 * multiplier); break;
            case '6': parsedValue = parsedValue + (6 * multiplier); break;
            case '7': parsedValue = parsedValue + (7 * multiplier); break;
            case '8': parsedValue = parsedValue + (8 * multiplier); break;
            case '9': parsedValue = parsedValue + (9 * multiplier); break;
            case '-': parsedValue = ~parsedValue; 
                // decrement by one due to twos complement difference
                *value = parsedValue+1;
                return noError;
                break;
            default: return cmdlineInvalidArg;
        }
        multiplier *= 10;
    }
    *value = parsedValue;
    return noError;
}

result cmdlineParseHex(char * token, int * value)
{
    int tokenLength = strlen(token);
    unsigned int multiplier = 1;
    int i = tokenLength;
    unsigned parsedValue = 0;
    while(i != 2)
    {
        i--;
        switch(token[i])
        {
            case '0':  break;
            case '1': parsedValue = parsedValue + (0x1 * multiplier); break;
            case '2': parsedValue = parsedValue + (0x2 * multiplier); break;
            case '3': parsedValue = parsedValue + (0x3 * multiplier); break;
            case '4': parsedValue = parsedValue + (0x4 * multiplier); break;
            case '5': parsedValue = parsedValue + (0x5 * multiplier); break;
            case '6': parsedValue = parsedValue + (0x6 * multiplier); break;
            case '7': parsedValue = parsedValue + (0x7 * multiplier); break;
            case '8': parsedValue = parsedValue + (0x8 * multiplier); break;
            case '9': parsedValue = parsedValue + (0x9 * multiplier); break;
            case 'A': case 'a': parsedValue = parsedValue + (0xA * multiplier); break;
            case 'B': case 'b': parsedValue = parsedValue + (0xB * multiplier); break;
            case 'C': case 'c': parsedValue = parsedValue + (0xC * multiplier); break;
            case 'D': case 'd': parsedValue = parsedValue + (0xD * multiplier); break;
            case 'E': case 'e': parsedValue = parsedValue + (0xE * multiplier); break;
            case 'F': case 'f': parsedValue = parsedValue + (0xF * multiplier); break;
            default: return cmdlineInvalidArg;
        }
        multiplier = multiplier << 4;
    }
    *value = (int) parsedValue;
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
            int arguments[CMDLINE_MAX_ARGS];
            // matched, parse arguments of commandline
            for(int j = 0; j < cmdLineEntries[i].argCnt; j++)
            {
                char *arg = strtok(NULL,STRTOK_DELIM);
                if(arg == NULL)
                    return cmdlineInvalidArg;
                result argparse = cmdlineParseArg(arg, &arguments[j]);
                if(argparse != noError)
                    return argparse;
            }
            // call the matched command with the argument count
            cmdLineEntries[i].argHandler(&arguments);
            return noError;
        }
    }
    return cmdlineNotFound;
}

