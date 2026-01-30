# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20251121
#
# Mini project makefile for mixed C and C++ projects

SOURCES ?= ../common.c90/minunit.c $(wildcard tests/*.c)
DEFINES :=
INCLUDES := -I. -I../common.c90
TARGET = template_minunit_c90_tests
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os
BUILD ?= DEBUG
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c90 $($(BUILD)) $(WARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
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

