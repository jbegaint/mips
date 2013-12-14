MIPS Simulator
==============

TODO
----
* pipeline implementation

* global cleaning
* assembly instructions test

Compilation:
------------

* `make simMips` or `make simMips-debug` (by default)

* `make check` to run test files


Execution:
----------

* `./simMips` to lauch the simulator

* `./simMips <filename>` to run a script (*.simcmd)

* `help` for more information

(Warning: by default `mipsel-linux-gnu-as` compiles in little endian, use option `-EB` to force big endian.)


Authors:
--------

* Bégaint J.

* Revolle M.


Links:
------

* http://stackoverflow.com/questions/384121/creating-a-module-system-dynamic-loading-in-c

* http://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit-in-c

* https://en.wikibooks.org/wiki/MIPS_Assembly/Pseudoinstructions

* http://www.cs.cornell.edu/courses/cs3410/2013sp/MIPS_Vol2.pdf