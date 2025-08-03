# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250803
#
# Mini project makefile for ANSI C projects

SOURCES ?= main.c
DEFINES :=
INCLUDES := -I./inc
TARGET = 8086dis
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wshadow -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c90 $(DEBUG) $(WARNINGS) $(INCLUDES) $(DEFINES)
CHECKFLAGS := -header-filter='.*'
LDLIBS := -lm
OUTPUT_OPTION = -MMD -MP -o $@

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(patsubst %.c,%.d,$(SOURCES))
EXECUTABLE := $(TARGET).elf

-include $(DEPS)

.PHONY: all
all: $(SOURCES) $(EXECUTABLE) tests.mak

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: check
check: $(SOURCES)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(SOURCES) -- $(CFLAGS) 

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
.PHONY: print-%
print-%: ; @echo $*=$($*)

