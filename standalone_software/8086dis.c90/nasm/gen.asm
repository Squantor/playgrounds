; Simple assembler file for dos
; Generate some machine code for tests
BITS 16
ORG 0x100
MOV AH, 0x4C
INT 21h