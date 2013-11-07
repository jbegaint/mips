Simulateur MIPS
===============

TODO
====

* implémenter les fonctions de l'interpréteur (Jean)
	
	* bp (done)
	* db
	* er
	* s
	* si
	* run

*init du tableau des pointeurs de fonctions

* implémenter toutes les instructions assembleurs en C. (execute_addi, execute_jal, etc...) (Marion)
pointeur de fonction :
typedef void (*display_instr) (ARCH, uint32_t)
typedef void (*execute_instr) (ARCH, uint32_t)
remplacer les fonctions de display_instru.c

* Pour la fonction run (Jean):
faire la boucle d'éxécution du programme
enum des états du programme chargé en mémoire
mettre en place la liste des bkp

*nettoyage de code:
(display_instruc)
uint32_t
nettoyage habituel
(parsing des paramètres)

*tests, tests everywhere


Compilation:
------------

* make simMips ou make simMips-debug (par défaut)

* make check pour lancer les tests


Exécution:
----------

* ./simMips pour utiliser le programme en mode intéractif

* ./simMips <filename> pour lancer un script (*.simcmd)


Auteurs:
--------

* Bégaint J.

* Revolle M.

