# SPDX-License-Identifier: MIT
# Copyright (c) 2021 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Single executable project

# Version: 202301027

# get the root directory of the build, used below for reproducable builds
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

# --- project settings ---
PROJECT := PC
DEFINES := 
LIBS :=
FILES := $(ROOT_DIR)/src/main.cpp \
$(ROOT_DIR)/src/test.cpp \
$(ROOT_DIR)/src/test.c
INCLUDES := -I$(ROOT_DIR)/inc
PREBUILD_SCRIPT := $(ROOT_DIR)/prebuild.sh
POSTBUILD_SCRIPT := $(ROOT_DIR)/postbuild.sh

# --- project build configuration settings ---

# --- Toolchain settings ---
MAKE := make
MKDIR := mkdir
RM := rm
TOOLCHAIN_PREFIX := 
C_COMPILER := gcc
CXX_COMPILER := g++
GDB := gdb
SIZE := size
AR := gcc-ar
OBJDUMP := objdump
OBJCOPY := objcopy
TOUCH := touch

# --- configurations ---
CONFIGS := debug release

#default flags
CFLAGS := -std=gnu11 -Wall -Wextra -c
CFLAGS_debug := -O0 -g3
CFLAGS_release := -O2 -g
CXXFLAGS := -std=c++20 -Wall -Wextra -c
CXXFLAGS_debug := -O0 -g3
CXXFLAGS_release := -O2 -g
ASMFLAGS := -c -x assembler-with-cpp
LDFLAGS +=
LDSCRIPT :=
DEFINES_release += -DNDEBUG
DEFINES_debug += -DDEBUG
FILES_debug := 
FILES_release := 
TARGET_LIBRARIES :=

# --- nothing user definable below ---

# --- useful variables ---
DATESTRING := $(shell date +%Y%m%d%H%M%S)
# root paths for various outputs
DOC_ROOT := $(ROOT_DIR)/doxyOutput
BIN_ROOT := $(ROOT_DIR)/bin
OBJ_ROOT := $(ROOT_DIR)/build

# Verbosity handling
ifeq ($(VERBOSE),1)
  C = 
  U = @true
else
  C = @
  U = @echo
endif

# --- sane defaults ---
.DEFAULT_GOAL := all
SHELL := bash
# .ONESHELL # commented out as it is incompatible in how we do verbosity
.SHELLFLAGS := -eu -o pipefail -c
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

# change recipe prefix to something more sensible then TAB
ifeq ($(origin .RECIPEPREFIX), undefined)
  $(error This Make does not support .RECIPEPREFIX. Please use GNU Make 4.0 or later)
endif
.RECIPEPREFIX = >

# --- build engine ---

# --- configuration management --
# load first config as default configuration
CONFIG ?= $(firstword $(CONFIGS))
# check if it is a valid configuration
ifeq (, $(filter $(CONFIG),$(CONFIGS)))
  $(error Unknown configuration $(CONFIG)! run make configurations to see available configurations)
endif

# transform configuration specific variables to variables used by the build
COPYVARS := FILES CFLAGS CXXFLAGS DEFINES
$(foreach V,$(COPYVARS),$(eval $(V) += $$($(V)_$(CONFIG))))
# specific handling for linker script
LDFLAGS += $(LDSCRIPT)
# add defines to flags
CFLAGS += $(DEFINES)
CXXFLAGS += $(DEFINES)
ASMFLAGS += $(DEFINES)
# substitute absolute paths with relative ones
CFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.
CXXFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.
ASMFLAGS += -fdebug-prefix-map=$(ROOT_DIR)=.

DOC_PATH := $(DOC_ROOT)
BIN_PATH := $(BIN_ROOT)/$(CONFIG)
OBJ_PATH := $(OBJ_ROOT)/$(CONFIG)
EXECUTABLE := $(BIN_PATH)/$(PROJECT).elf
SIZELOG_PATH := $(ROOT_DIR)/

# create file creation prerequisites 
BINDEPS := $(OBJ_PATH)/build-tag $(BIN_PATH)/build-tag
DOCDEPS := $(DOC_PATH)/build-tag
# create lists of prerequisites for the project
PROJECT_OBJECTS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$(FILES)))
OBJECTS := $(addprefix $(OBJ_PATH)/, $(addsuffix .o,$(FILES)))
DEPS := $(OBJECTS:.o=.d)

all: $(BINDEPS) $(EXECUTABLE)

.PHONY: all

-include $(DEPS)

$(DOC_PATH)/build-tag:
> $(C)$(MKDIR) -p $(DOC_PATH)
> $(C)$(TOUCH) $@

$(BIN_PATH)/build-tag:
> $(C)$(MKDIR) -p $(BIN_PATH)
> $(C)$(TOUCH) $@

$(OBJ_PATH)/build-tag:
> $(C)$(MKDIR) -p $(OBJ_PATH)
> $(C)$(TOUCH) $@
ifdef $(PROJECT)_PREBUILD_SCRIPT
> $(U) "PRE $($(PROJECT)_PREBUILD_SCRIPT)"
> $(SHELL) $($(PROJECT)_PREBUILD_SCRIPT)
endif

doc: $(DOCDEPS)
> $(C)$(MKDIR) -p $(DOC_PATH)
> $(C)doxygen doxygen.doxy
.PHONY: doc

$(EXECUTABLE): $(OBJECTS)
> $(U) "Linking $(EXECUTABLE)"
> $(C)$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(LDFLAGS) $(PROJECT_OBJECTS) -Xlinker -Map="$@.map" -o $@
> $(C)date >> $(SIZELOG_PATH)size$(CONFIG).log
> $(C)$(TOOLCHAIN_PREFIX)$(SIZE) $@ >> $(SIZELOG_PATH)size$(CONFIG).log
> $(C)$(TOOLCHAIN_PREFIX)$(OBJCOPY) -R .stack -O binary $@ $(BIN_PATH)/$(PROJECT).bin
> $(C)$(TOOLCHAIN_PREFIX)$(OBJDUMP) -h -S "$@" > "$(BIN_PATH)/$(PROJECT).lss"
ifdef $(PROJECT)_POSTBUILD_SCRIPT
> $(U) "POST $($(PROJECT)_POSTBUILD_SCRIPT)"
> $(SHELL) $($(PROJECT)_POSTBUILD_SCRIPT)
endif

$(BIN_PATH)/%.a: $(OBJECTS)
> $(U) "AR  $(basename $(notdir $@))"
> $(C)$(TOOLCHAIN_PREFIX)$(AR) rs $@ $($*_OBJECTS)

$(OBJ_PATH)/%.c.o: %.c
> $(U) "C   $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(CFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

$(OBJ_PATH)/%.cpp.o: %.cpp
> $(U) "C++ $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(CXX_COMPILER) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

$(OBJ_PATH)/%.S.o: %.S
> $(U) "ASM $(basename $(notdir $@))"
> $(C)$(MKDIR) -p $(dir $@) 
> $(C)$(TOOLCHAIN_PREFIX)$(C_COMPILER) $(ASMFLAGS) $(INCLUDES) -MP -MMD -c -o $@ $<

clean: $(BINDEPS) $(DOCDEPS)
> $(U) "Cleaning"
> $(C)$(RM) -rf $(BIN_ROOT)
> $(C)$(RM) -rf $(OBJ_ROOT)
> $(C)$(RM) -rf $(DOC_ROOT)
.PHONY: clean

# utility rules
configurations:
> @/bin/echo -e "available configurations:\n $(addsuffix \n,$(CONFIGS))"
.PHONY: configurations

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging
print-%: ; @echo $*=$($*)
.Phony: print-%
