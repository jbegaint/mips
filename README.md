Simulateur MIPS
===============

TODO
====

* implémenter les fonctions de l'interpréteur (Jean)
	
	* bp (done)
	* db (done)
	* er (done)
	* s (done)
	* si
	* run (done)

* init des "plugins"

* implémenter toutes les instructions assembleurs en C. (execute_addi, execute_jal, etc...) (Marion)
pointeur de fonction :
typedef void (*display) (uint32_t)
typedef void (*execute) (ARCH, uint32_t)
remplacer les fonctions de display_instru.c

* nettoyage de code:
	* (display_instruc)
	* uint32_t
	* nettoyage habituel
	* (parsing des paramètres)

* tests, tests everywhere

---

* clean parse_args


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

Links:
------

* http://stackoverflow.com/questions/384121/creating-a-module-system-dynamic-loading-in-c
* 

