#ifndef AFFICHE_INSTRU_H_INCLUDED
#define AFFICHE_INSTRU_H_INCLUDED

#include "desc/desc.h"

#define NO_MATCH -1

int affichage_instr(uint val, DESC *tab);
int afficher_typeR(DESC *R ,int c, uint val);
int afficher_typeI(DESC *JI ,int c, uint val);
int afficher_typeJ( DESC *JI ,int c, uint val);

int matchR(uint function, DESC *R);
int matchJI(uint opcode, DESC *JI );

#endif // AFFICHE_INSTRU_H_INCLUDED
