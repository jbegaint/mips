Simulateur MIPS
===============

TODO
====

* fix deliberate(?) leak in load_desc_so
* clean helpers, utils, des

Compilation:
------------

* make simMips ou make simMips-debug (par défaut)

* make check pour lancer les tests


Exécution:
----------

* ./simMips pour utiliser le programme en mode intéractif

* ./simMips <filename> pour lancer un script (*.simcmd)

* help pour plus d'informations

(Warning: by default `mipsel-linux-gnu-as` compiles in little endian, use -EB to force big endian.)


Auteurs:
--------

* Bégaint J.

* Revolle M.

Links:
------

* http://stackoverflow.com/questions/384121/creating-a-module-system-dynamic-loading-in-c

* http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c