# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250410
#
# Mini project makefile for ANSI C projects

SOURCES ?= $(wildcard *.c)
INCLUDES := -I.
TARGET = minunit_c90
CC = gcc
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c90 $(DEBUG) $(WARNINGS) $(INCLUDES)
LDLIBS := -lm
OUTPUT_OPTION = -MMD -MP -o $@


OBJECTS := $(SOURCES:.c=.o)
DEPS := $(SOURCES:.c=.d)
EXECUTABLE := $(TARGET).elf
-include $(DEPS)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDLIBS) $(OBJECTS) -o $(EXECUTABLE)

%.o.c: %.c
	$(CC) $(CFLAGS) $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
print-%: ; @echo $*=$($*)
.Phony: print-%