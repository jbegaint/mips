# Attention ne pas essayer d'assembler ou d'executer ce code les
# LW et SW ne seront pas corrects car elles accèdent directement 
# à la section TEXT. SW ecrase notamment la première instruction
# avec un NOP...
# le div est par défaut entouré d'instructions pour gerer la
# division par zero. Dans le .o ces instructions ont été enlevées
# le code .o n'est donc compatible qu'avec l'emulateur lorsque 
# la gestion de la relocation n'est pas active et en assumant une 
# section TEXT logée à 0x0
 
# code qui ne fait rien d'autre que tester les instructions suivantes


addi $t1,$zero,2
addi $t2,$zero,4
mult $t2,$t1
div $t2,$t1
mfhi $t3
mflo $t4
lw $t5,0x28($zero) # recuperer le code de MFHI
sw $zero,0($zero) #ecrase la premiere instruction avec un NOP

