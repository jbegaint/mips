# programme qui fait une boucle en incrementant un registre

.set nomove # demande à l'assembleur de respecter l'ordre des instructions mais permet des optimisations de boucles

_start:
.global _start
addi $t1,$zero,12 # set $t1 a 12
add $t2,$zero,$zero # set $t2 à zéro
addi $t2,$t2,1 # incremente
bne $t2,$t1,-8 # boucle sur l'increment tant que $t1 et $t2 sont differents
add $t2,$zero,$zero # remise a zero de $t2 dans le delay slot du branchement (risque de boucle infinie), l'assembleur va automatiquement ajouter un NOP


.data 
X: .word 4
