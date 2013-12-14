## test all instructions
## not supposed to be run

_start:
.global _start
	addi  $t0,$0,21
	addi  $t1,$0,2
	div   $t0,$t1 # divise 21 par 2 il doit
	nop           # rester 10 dans LO
	nop           # et 1 dans LI
	nop
	