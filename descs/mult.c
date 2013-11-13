#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

void display_mult(ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
    fprintf(stdout,"MULT $%u, $%u\n",rs,rt);

    return;
}

void execute_mult(ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;
	uint64_t result;
	uint64_t isol_lo=0;
	uint64_t isol_hi=0;


    parser_typeR(word,&rs,&rt,&rd,&sa);
	reslut = rs*rt;

    for (i=0; i<32; i++){
        isol_lo |= (1<<i) ;
    }
    for (i=32; i<64; i++){
        isol_hi |= (1<<i) ;
    }
	
	set_LO(arch, isol_lo & word);
	set_HI(arch, isol_hi & word);
	
	return ;
}

