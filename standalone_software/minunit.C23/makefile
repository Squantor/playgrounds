# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20251005
#
# Mini project makefile for C23 C projects

SOURCES ?= $(wildcard *.c)
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I.
TARGET = minunit_C23
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wshadow -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c2x $(DEBUG) $(WARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
CHECKFLAGS := -header-filter='.*'
LDLIBS := -lm

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(patsubst %.c,%.d,$(SOURCES))
EXECUTABLE := $(TARGET).elf

-include $(DEPS)

.PHONY: all
all: $(SOURCES) $(EXECUTABLE) makefile

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

