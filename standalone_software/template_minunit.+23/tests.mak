# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20260624
#
# Mini project makefile for mixed C and C++ tests with coverage

BUILD ?= RELEASE
CSOURCES := $(wildcard tests/*.c)
CPPSOURCES := $(wildcard tests/*.cpp)
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I. -Itests
TARGET = minunit_C++23_tests
CC = gcc
CPP = g++
SIZE = size
DEBUG_CFLAGS = -g3 -O0
RELEASE_CFLAGS = -g3 -Os -flto
RELEASE_LFLAGS = -flto
COVERAGE_CFLAGS = -g0 -O0 --coverage
COVERAGE_LFLAGS = --coverage
CWARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS = -std=c2x $($(BUILD)_CFLAGS) $(CWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
CPPWARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CPPFLAGS = -std=c++20 -fno-rtti -fno-exceptions $($(BUILD)_CFLAGS) $(CPPWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
LDLIBS = -lm
LDFLAGS = $($(BUILD)_LFLAGS) $(LDLIBS) -fsanitize=undefined
CHECKFLAGS = -header-filter='.*'

BUILDDIR := build
MAKEFILE_NAME := $(lastword $(MAKEFILE_LIST))
OBJDIR = $(BUILDDIR)/$(BUILD)
SOURCES := $(CSOURCES) $(CPPSOURCES)
OBJECTS = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(SOURCES)))
COVOBJS = $(addsuffix .gcno,$(SOURCES)) $(addsuffix .gcda,$(SOURCES)) coverage.*
DEPS = $(OBJECTS:.o=.d)
EXECUTABLE := $(OBJDIR)/$(TARGET).elf

.PHONY: all
all: $(EXECUTABLE)

.PHONY: debug
debug:
	$(MAKE) -f$(MAKEFILE_NAME) BUILD=DEBUG all

.PHONY: release
release:
	$(MAKE) -f$(MAKEFILE_NAME) BUILD=RELEASE all

.PHONY: coverage
coverage:
	$(MAKE) -f$(MAKEFILE_NAME) BUILD=COVERAGE coverage-run

.PHONY: run
run: all
	./$(EXECUTABLE)

.PHONY: check
check: $(SOURCES)
ifneq ($(CSOURCES),)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(CSOURCES) -- $(CFLAGS)
endif
ifneq ($(CPPSOURCES),)
	clang-tidy --config-file=.clang-tidy $(CHECKFLAGS) $(CPPSOURCES) -- $(CPPFLAGS)
endif

.PHONY: coverage-run
coverage-run: $(EXECUTABLE)
	./$(EXECUTABLE)
	gcovr -r . --exclude tests/ --html-details coverage.html

$(EXECUTABLE): $(OBJECTS) makefile
	@echo This build is a $(BUILD) build
	$(CPP) $(OBJECTS) -o $@ $(LDFLAGS)
	$(SIZE) $@

$(OBJDIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) coverage.*

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)
