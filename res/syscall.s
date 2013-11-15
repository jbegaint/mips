.set nomove
.text

LUI $t1,0xF000
ROTR $t1,$t1,4
SLL $t1,$t1,2
SRL $t1,$t1,2
SLT $t2,$0,$t1
sub $t1,$zero,$t1
syscall
addi $t1,$t1,1
addi $t1,$t1,1
addi $t1,$t1,1
addi $t1,$t1,1
