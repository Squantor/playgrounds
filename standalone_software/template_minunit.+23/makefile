# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20260624
#
# Mini project makefile for mixed C and C++ projects

BUILD ?= RELEASE
CSOURCES := $(wildcard *.c)
CPPSOURCES := $(wildcard *.cpp)
DEFINES := -DMINUNIT_MAX_TESTS=100
INCLUDES := -I.
TARGET = minunit_C++23
CC = gcc
CPP = g++
SIZE = size
DEBUG_CFLAGS = -g3 -O0
RELEASE_CFLAGS = -g3 -Os -flto
RELEASE_LFLAGS = -flto
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
	rm -rf $(BUILDDIR)

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)
