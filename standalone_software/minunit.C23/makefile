# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250729
#
# Mini project makefile for ANSI C projects

SOURCES ?= $(wildcard *.c)
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I.
TARGET = minunit_c90
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c2x $(DEBUG) $(WARNINGS) $(INCLUDES) $(DEFINES)
LDLIBS := -lm
OUTPUT_OPTION = -MMD -MP -o $@

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(patsubst %.c,%.d,$(SOURCES))
EXECUTABLE := $(TARGET).elf

-include $(DEPS)

.PHONY: all
all: $(SOURCES) $(EXECUTABLE) makefile

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDLIBS) $(OBJECTS) -o $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
print-%: ; @echo $*=$($*)
.Phony: print-%
