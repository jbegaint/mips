#ifndef PARSER_INSTRU_H_INCLUDED
#define PARSER_INSTRU_H_INCLUDED

#include "arch/arch.h"

uint parser_instr(uint val , uchar strat, uchar stop);

int parser_typeR(uint val , uint *rs, uint *rt, uint *rd, uint *sa);
int parser_typeI(uint val, uint *rs, uint *rt, uint *immediate);
int parser_typeJ(uint val, uint *target);

#endif // PARSER_INSTRU_H_INCLUDED
