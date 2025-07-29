# 8086 machine code disassembler
Simple project that disassembles .COM and .EXE files into a NASM file. 
## build instructions
This project contains two makefiles, one is for the actual program, one is for the unittests.
To build the main executable: ```make```
To cleanup: ```make clean```
To execute ```make run```
To run the unittests use ```make -f tests.mak run```
## Status
* Implement MOV and INT instruction disassembly
* Implement COM file parsing and disassembly
* Implement all 8086 instructions
* Implement EXE file parsing and disassembly
