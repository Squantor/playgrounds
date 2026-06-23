# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20260623
#
# Mini project makefile for mixed C and C++ projects

CSOURCES := $(wildcard tests/*.c)
CPPSOURCES := $(wildcard tests/*.cpp)
CPPSOURCES += cobs.cpp
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

SOURCES := $(CSOURCES) $(CPPSOURCES)
OBJECTS := $(addsuffix .o,$(SOURCES))
DEPS := $(patsubst %.o,%.d,$(OBJECTS))
EXECUTABLE := $(TARGET).elf

.PHONY: all
all: $(EXECUTABLE)
all: BUILD=DEBUG

.PHONY: debug
debug: BUILD=DEBUG
debug: clean $(EXECUTABLE)

.PHONY: release
release: BUILD=RELEASE
release: clean $(EXECUTABLE)

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

.PHONY: coverage
coverage: BUILD=COVERAGE
coverage: clean $(EXECUTABLE)
	@echo BUILD=$(BUILD)
	./$(EXECUTABLE)
	gcovr -r . \
		--exclude tests/ \
		--html-details coverage.html

$(EXECUTABLE): $(OBJECTS) makefile
	@echo BUILD=$(BUILD)
	$(CPP) $(OBJECTS) -o $@ $(LDFLAGS)
	$(SIZE) $@

%.c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.cpp.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPS) $(EXECUTABLE) coverage.*
	-find . -name '*.gcda' -delete
	-find . -name '*.gcno' -delete

-include $(DEPS)

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
.PHONY: print-%
print-%: ; @echo $*=$($*)

