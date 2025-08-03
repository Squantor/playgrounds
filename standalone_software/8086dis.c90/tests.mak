# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250412
#
# Mini project makefile for ANSI C projects

SOURCES ?= testmain.c minunit.c x86isn.c hmov.c qisn.c parseisn.c \
$(wildcard tests/*.c)
# tests/mov.c tests/x86isn.c tests/qisn.c
DEFINES := -D TESTS
INCLUDES := -Iinc
TARGET = 8086dis_tests
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c90 $(DEBUG) $(WARNINGS) $(INCLUDES) $(DEFINES)
LDLIBS := -lm
OUTPUT_OPTION = -MMD -MP -o $@

OBJECTS := $(patsubst %.c,%.o,$(SOURCES))
DEPS := $(patsubst %.c,%.d,$(SOURCES))
EXECUTABLE := $(TARGET).elf

-include $(DEPS)

all: $(SOURCES) $(EXECUTABLE) tests.mak

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
