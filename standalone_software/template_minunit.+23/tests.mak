# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20260130
#
# Mini project makefile for mixed C and C++ projects

CSOURCES := ../common.+23/minunit.c $(wildcard tests/*.c)
CPPSOURCES := $(wildcard tests/*.cpp)
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I. -I../common.+23
TARGET = minunit_C++23_tests
CC = gcc
CPP = g++
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os
BUILD ?= DEBUG
CWARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c2x $($(BUILD)) $(CWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
CPPWARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CPPFLAGS := -std=c++20 -fno-rtti -fno-exceptions $($(BUILD)) $(CPPWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
LDLIBS := -lm
CHECKFLAGS := -header-filter='.*'

SOURCES := $(CSOURCES) $(CPPSOURCES)
OBJECTS := $(addsuffix .o,$(SOURCES))
DEPS := $(patsubst %.o,%.d,$(OBJECTS))
EXECUTABLE := $(TARGET).elf

.PHONY: all
all: $(EXECUTABLE)

.PHONY: run
run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: check
check: $(SOURCES)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(CSOURCES) -- $(CFLAGS)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(CPPSOURCES) -- $(CPPFLAGS)

$(EXECUTABLE): $(OBJECTS) makefile
	$(CPP) $(OBJECTS) -o $@ $(LDLIBS)
	$(SIZE) $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)

