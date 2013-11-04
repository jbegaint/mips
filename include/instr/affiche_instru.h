#ifndef AFFICHE_INSTRU_H_INCLUDED
#define AFFICHE_INSTRU_H_INCLUDED

#include "desc/desc.h"

#define NO_MATCH -1

int display_instr(uint val);
int display_typeR(int c, uint val);
int display_typeI(int c, uint val);
int display_typeJ(int c, uint val);

int matchR(uint function);
int matchJI(uint opcode);

#endif // AFFICHE_INSTRU_H_INCLUDED
