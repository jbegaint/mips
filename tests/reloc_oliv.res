CMD TEST RESULT 0xb
00000000: 20 0a 10 00 ADDI $10, $0, 4096
00000004: 20 0b 00 01 ADDI $11, $0, 1
00000008: 20 0c 00 42 ADDI $12, $0, 66
0000000c: 11 6a 00 01 BEQ $11, $10, 4
00000010: 00 00 00 00 NOP

<trololo>:
00000014: 3c 01 00 00 LUI $1, 0x0
00000018: ac 2c 10 04 SW $12, 1004($1)
0000001c: 00 00 00 00 NOP

<end>:
00000020: 3c 04 00 00 LUI $4, 0x0
00000024: 8c 84 10 04 LW $4, 4100($4)
00000028: 00 00 00 00 NOP
0000002c: 00 00 00 0c SYSCALL
ADDI $10, $0, 4096
ADDI $11, $0, 1
ADDI $12, $0, 66
BEQ $11, $10, 14
NOP
LUI $1, 0x0
SW $12, 1004($1)
NOP
LUI $4, 0x0
LW $4, 4100($4)
NOP
SYSCALL
