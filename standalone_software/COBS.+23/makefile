# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20260703
#
# Mini project makefile for mixed C and C++ tests with coverage and doxygen

BUILD ?= RELEASE
ASMSOURCES :=
CSOURCES := $(wildcard tests/*.c)
CPPSOURCES := $(wildcard tests/*.cpp)
CPPSOURCES += cobs.cpp
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I. -Itests
TARGET = COBS_tests
CC = gcc
CPP = g++
SIZE = size
DEBUG_CFLAGS = -g3 -Og
DEBUG_LFLAGS = 
RELEASE_CFLAGS = -g3 -Os -flto
RELEASE_LFLAGS = -flto
COVERAGE_CFLAGS = -g0 -O0 --coverage
COVERAGE_LFLAGS = --coverage
ASMFLAGS = -x assembler-with-cpp $(INCLUDES) $(DEFINES) -MP -MMD
CWARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -Wstrict-prototypes -Wvla -fsanitize=undefined -fsanitize-trap
CFLAGS = -std=c2x $($(BUILD)_CFLAGS) $(CWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
CPPWARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wdouble-promotion -Wno-sign-conversion -fsanitize=undefined -fsanitize-trap
CPPFLAGS = -std=c++20 -fno-rtti -fno-exceptions $($(BUILD)_CFLAGS) $(CPPWARNINGS) $(INCLUDES) $(DEFINES) -MMD -MP
LDLIBS = -lm
LDFLAGS = $($(BUILD)_LFLAGS) $(LDLIBS) -fsanitize=undefined
CHECKFLAGS = -header-filter='.*'

BUILDDIR := build
DOCDIR := $(BUILDDIR)/doxygen
MAKEFILE_NAME := $(lastword $(MAKEFILE_LIST))
OBJDIR = $(BUILDDIR)/$(BUILD)
SOURCES := $(ASMSOURCES) $(CSOURCES) $(CPPSOURCES)
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

.PHONY: documentation
documentation:
	mkdir -p $(DOCDIR)
	cat doxygen/Doxyfile ; echo "@INCLUDE = $(TARGET).doxy" | doxygen -

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
	gcovr -r . --exclude tests/ --html-details $(BUILDDIR)/coverage.html

$(EXECUTABLE): $(OBJECTS) makefile
	@echo This build is a $(BUILD) build
	$(CPP) $(LDFLAGS) $(OBJECTS) -o $@ $(LDLIBS)
	$(SIZE) $@

$(OBJDIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%.S.o: %.S
	mkdir -p $(dir $@)
	$(CC) $(ASMFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)

