# SPDX-License-Identifier: MIT
# Copyright (c) 2025 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# Version: 20250810
#
# Mini project makefile for NASM projects

gen.COM: nasm/gen.asm
	nasm -f bin $^ -o $@

.PHONY: all
all: gen.COM

.PHONY: clean
clean:
	rm -f *.COM