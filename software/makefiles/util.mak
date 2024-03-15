# SPDX-License-Identifier: MIT
# Copyright (c) 2024 Bart Bilos
# For conditions of distribution and use, see LICENSE file

#
# Version: 20240415

# various utilities present here

# generate disassembly of currently built executable
generate-disassembly: $(EXECUTABLE) $(PROJ_DIR)/disassemblies/build-tag
> $(C)$(TOOLCHAIN_PREFIX)$(OBJDUMP) -h --no-show-raw-insn --no-addresses -S "$(EXECUTABLE)" > "$(PROJ_DIR)/disassemblies/$(PROJECT)_$(DATESTRING).lss"

.PHONY: generate-disassembly

$(PROJ_DIR)/disassemblies/build-tag: 
> $(C)$(MKDIR) -p $(PROJ_DIR)/disassemblies
> $(C)$(TOUCH) $@

projects:
> @/bin/echo -e "available projects:\n $(addsuffix \n,$(PROJECTS))"
.PHONY: projects

libraries:
> @/bin/echo -e "available libraries:\n $(addsuffix \n,$(LIBRARIES))"
.PHONY: libraries

help:
> @echo to build a project use \"make PROJECT=project\"
> @echo for a list of all projects run \"make projects\"
> @echo for a list of available libraries rune \"make libraries\"
> @echo use VERBOSE=1 to enable verbose output
> @echo additional commands are:
> @echo \"make generate-disassembly\" for generating disassembly of the program

.PHONY: help