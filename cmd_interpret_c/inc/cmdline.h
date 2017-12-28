/*
The MIT License (MIT)

Copyright (c) 2017 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

/*
 * cmdline.h
 *
 *  Created on: Dec 27, 2017
 *      Author: abilos
 *
 * Simple command interpreter library, accepts commands in the shape of a string
 * with 0 or more arguments, each argument is a decimal or hex number.
 *
 *
 */

#ifndef INC_CMD_INTERPRET_H_
#define INC_CMD_INTERPRET_H_

#include <stdint.h>
#include "results.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMDLINE_MAX_ARGS    6

// all the data one command should include
typedef struct {
    // trigger string
    char * strTrigger;
    // help string (always useful
    char * strHelp;
    // argument count
    uint8_t argCnt;
    // function(int arglist)
} cmdLineEntry;

result cmdlineParse(char * line);

#ifdef __cplusplus
}
#endif

#endif /* INC_CMD_INTERPRET_H_ */
