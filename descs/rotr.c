#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

void display(uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	fprintf(stdout,"RTOR $%u, $%u, $%u\n",rd,rt,sa);
	return;
}

void execute(ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;
	uint32_t isol_high=0;
	uint32_t isol_low=0;

    parser_typeR(word,&rs,&rt,&rd,&sa);

    for (i=0; i<sa; i++){
        isol_low |= (1<<i) ;
    }
    for (i=sa; i<32; i++){
        isol_high |= (1<<i) ;
    }

	isol_high = isol_high & rt;
	isol_low = isol_low & rt;

	
	return ;
}

