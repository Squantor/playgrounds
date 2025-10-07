# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20251007
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
DEPS := $(patsubst %.o,%.d,$(OBJECTS))
EXECUTABLE := $(TARGET).elf

.PHONY: all
all: $(EXECUTABLE)

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: check
check: $(SOURCES)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(SOURCES) -- $(CFLAGS) 

$(EXECUTABLE): $(OBJECTS) makefile
	$(CC) $(OBJECTS) -o $@ $(LDLIBS)
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)

