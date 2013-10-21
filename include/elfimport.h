/**
 * PHELMA - Projet Informatique
 * @author (c) Laurent Fesquet 2003,
 * @author (m) Matthieu Chabanas 2005
 * @author (m) François Portet 2013 <francois.portet@imag.fr>
 * @brief Importation de la librairie LIBELF
 */


#ifndef _ELFIMPORT_
#define _ELFIMPORT_

/* MIPS main relocation types */
#define R_MIPS_NONE            0
#define R_MIPS_16              1
#define R_MIPS_32              2
#define R_MIPS_REL32           3
#define R_MIPS_26              4
#define R_MIPS_HI16            5
#define R_MIPS_LO16            6
#define R_MIPS_GPREL16         7
#define R_MIPS_LITERAL         8
#define R_MIPS_GOT16           9
#define R_MIPS_PC16            10
#define R_MIPS_CALL16          11
#define R_MIPS_GPREL32         12
#define R_MIPS_GOTHI16         21
#define R_MIPS_GOTLO16         22
#define R_MIPS_CALLHI16        30
#define R_MIPS_CALLLO16        31


/* LIBELF library */
#include <libelf.h>


#endif /* _ELFIMPORT_ */
