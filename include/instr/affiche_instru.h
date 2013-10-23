#ifndef AFFICHE_INSTRU_H_INCLUDED
#define AFFICHE_INSTRU_H_INCLUDED

#include "desc/desc.h"

int affichage_instr(uint val, DESC *R, DESC *JI);
int afficher_typeR(DESC *R ,int c, uint val);
int afficher_typeI(DESC *JI ,int c, uint val);
int afficher_typeJ( DESC *JI ,int c, uint val);

int matchR(uint function, DESC *R);
int matchJI(uint opcode, DESC *JI );

#endif // AFFICHE_INSTRU_H_INCLUDED
