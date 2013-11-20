.set noreorder
.text 

ADDI $4,$zero,12345  # met 12345 dans le registre $4
JAL write            # Appel à la procédure "write"  
NOP                  # delay slot 
B end                # On revient ici après le "write" branchement vers la fin 
NOP

write:
sw $4,Z              # écrit le contenu de $4 à l'adresse de Z
JR $31               # fin de la procédure, retour à l'appelant
NOP

end:
syscall              # la fin consiste en un appel explicite à syscall pour sortir du programme


.data 
X: .byte 0xAB        # un octet initialisé à AB à l'adresse X
Y: .word Z           # un mot de 32 bits initialisé à la valeur de Z 
Z: .word 0           # un mot de 32 bits initialisé à zéro à l'adresse Z
