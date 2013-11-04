## test all instructions
## not supposed to be run

.data
.space 80

.text
ADD $8, $9, $10	
ADDI $8, $8, 18	
AND $8, $9, $10	
BEQ $8, $8, 4
BGTZ $8, 12
BLEZ $8, 12
BNE $2, $3, 40
#DIV $5, $6
JAL 12
J 4
JR $10
LUI $10, 9
LW $24, 15
MFHI $27
MFLO $25
MULT $4, $5
NOP
OR $4, $5, $6
SLL $10, $11, $12
SLT $13, $14, $15
#SRL $16, $17, $18
SUB $19, $20, $21
SW $22, 10
XOR $4, $5, $6

.bss
Tab: 
.space 80	
