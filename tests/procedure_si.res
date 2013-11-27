CMD TEST RESULT 0xb
ADDI $9, $0, 8
ADD $10, $0, $9
SLL $9, $9, $2
JAL 24 <procedure>
SRL $9, $9, $2
JR $31 
BEQ $9, $10, 2c
NOP
NOP
