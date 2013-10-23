#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arch/arch.h"

#include "instr/parser_instru.h"

uint parser_instr (uint val , uchar start, uchar stop)
{
    int i;
    uint isol = 0;
    uint res;

    for (i=start; i<stop+1; i++){

        isol |= (1<<i) ;

    }
    res = val & isol;
    res = res>>start;

    return res;
}


int parser_typeR(uint val , uint *rs, uint *rt, uint *rd, uint *sa)
{
    *rs = parser_instr(val, 21, 25 );
    *rt = parser_instr(val, 16, 20 );
    *rd = parser_instr(val, 11, 15 );
    *sa = parser_instr(val, 6, 10 );

    return 1;
}

int parser_typeI(uint val, uint *rs, uint *rt, uint *immediate)
{
    *rs = parser_instr(val, 21, 25 );
    *rt = parser_instr(val, 16, 20 );
    *immediate = parser_instr(val, 0, 15 );

    return 1;
}
int parser_typeJ(uint val, uint *target)
{
    *target = parser_instr(val, 0, 25 );
    return 1;
}