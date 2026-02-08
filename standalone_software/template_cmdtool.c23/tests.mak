# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20251121
#
# Mini project makefile for mixed C and C++ projects

SOURCES := $(wildcard tests/*.c)
SOURCES += par_arg.c
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I. -Itests
TARGET = template_cmdtool_c23_tests
CC = gcc
CXX = g++
SIZE = size
DEBUG = -g3 -O0
RELEASE = -g3 -Os
BUILD ?= DEBUG
CWARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS := -std=c2x $($(BUILD)) $(CWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
CXXWARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CXXFLAGS := -std=c++20 -fno-rtti -fno-exceptions $($(BUILD)) $(CXXWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
LDLIBS := -lm
CHECKFLAGS := -header-filter='.*'
LDLIBS := -lm

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
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(SOURCES) -- $(CFLAGS) 

$(EXECUTABLE): $(OBJECTS) makefile
	$(CXX) $(OBJECTS) -o $@ $(LDLIBS)
	$(SIZE) $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE)

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)

