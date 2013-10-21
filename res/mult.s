## Fichier mult.s : un programme qui fait une multiplication et une division
.text            
.set noreorder		#pas de reordonnancement

##----------------------------------------------------------------------------
# Programme principal
  ADDI  $t9,$zero,EXIT
  addi  $t2,$zero,-	43     	# $t2 <- -43
  addi  $t3,	$0,0xff      	# $t3 <- 0xff

# appel de la procedure min
  DIV  $t2,$t3			# divise les deux nombres
  MFLO $t0 			# prend le quotient du résultat de la division
  MFHI $t1 			# prend le reste du résultat de la division
  BEQ $t1,$zero, mult           # si il n'y a pas de reste alors on peut tester dans l'autre sens
  J EXIT			# saut à la sortie sinon  		


mult: 
  NOP				# quelques non opération pour respecter la consigne 
  NOP				# de la doc concernant le MFHI
  mult $t0,$t3			# on essaye de retrouver le nombre de départ
  MFLO $t0 			# prend la partie basse de la multiplication
  MFHI $t1 			# prend la partie haute de la multiplication
	nop
nop
  add $t5,$zero,$zero
  BNE $t1,$t5,EXIT		# si le résultat est trop grand on sort
  BEQ $t0,$t2,reussi		# si $t2 et $t0 sont egaux on a retrouvé le resultat
  J EXIT			# sinon on sort
reussi:
  addi $t2,$zero,0x1		# si reussi on set $t2 à 1
  J EXIT			# et on sort


EXIT	:
syscall
## The End

.data
.byte 12,0xAA,0xBB,0xCC,0xdd
.byte 0xFF
.word 0xAABBCCDD
