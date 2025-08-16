; Simple assembler file for dos
; Generate some machine code for tests
CPU 8086
BITS 16
ORG 0x100
NOP
MOV AX, [testword]
MOV AL, [testbyte]
NOP
MOV CH, 0x42
MOV DX, 0x4401
NOP
MOV DL, CH
MOV DI, CX
NOP
MOV AH, [BX]
MOV BL, [0x1234]
MOV CX, [BP+SI+-4]
MOV DX, [SI+0x1234]
NOP
MOV [SI], DH
MOV [0x2569], CL
MOV [BX+DI+-4000], DI
MOV [BP+DI+44], SP
NOP
MOV ES, BP
MOV ES,[SI+1234]
MOV BX, DS
MOV [testword], CS
NOP
MOV AH, 0x4C
INT 21h
testbyte:    db  0x42
testword:    dw  0xbeef