#ifndef GET_INSTR_H_INCLUDED
#define GET_INSTR_H_INCLUDED


#define MATCH 1
#define NO_MATCH 0

#include "arch/arch.h"

int matchR(uint function);
int matchJI(uint opcode);
int get_instr(uint val);


#endif // GET_INSTR_H_INCLUDED
