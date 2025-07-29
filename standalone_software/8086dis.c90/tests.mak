# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250412
#
# Mini project makefile for ANSI C projects

SOURCES ?= testmain.c minunit.c tests.c
INCLUDES := -I.
TARGET = minunit_c90
CC = gcc
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os 
WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c90 $(DEBUG) $(WARNINGS) $(INCLUDES)
LDLIBS := -lm
OUTPUT_OPTION = -MMD -MP -o $@


OBJECTS := $(addsuffix .o,$(SOURCES))
DEPS := $(addsuffix .d,$(SOURCES))
EXECUTABLE := $(TARGET).elf
-include $(DEPS)

all: $(SOURCES) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDLIBS) $(OBJECTS) -o $@
	$(SIZE) $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION)

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
print-%: ; @echo $*=$($*)
.Phony: print-%