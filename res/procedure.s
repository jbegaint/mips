# programme qui fait appel a une procedure (JAL)
# se contente de verifier qu'un decalage à gauche puis à droite donne la valeur initiale


.set noreorder    # ne pas modifier l'ordre des instructions ne fait meme pas des optimisations de boucle (les NOP sont mis de manière explicite)

_start:
.global _start

addi $t1,$zero,8
add $t2,$zero,$t1
SLL $t1,$t1,2
JAL 36          # appel explicite à l'adresse de la procedure  
NOP
BEQ $t1,$t2,20  # branchement à OK si les deux valeurs sont égales
NOP
J 48 						# sinon saut à KO
NOP
procedure:
SRL $t1,$t1,2
JR $31

OK:
nop
KO:
nop
