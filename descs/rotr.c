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
	uint32_t val_rt;
	uint32_t val_sa;
	/*uint32_t val_rd;*/
    uint i;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	val_rt = (arch->registers)[rt];
	val_sa = (arch->registers)[sa];

    for (i=0; i<val_sa; i++){
        isol_low |= (1<<i) ;
    }
    for (i=sa; i<32; i++){
        isol_high |= (1<<i) ;
    }

	isol_high = isol_high & val_rt;
	isol_low = isol_low & val_rt;
	isol_high = isol_high >> (32-val_sa);
	isol_low = isol_low << val_sa;

	(arch->registers)[rd] = isol_low | isol_high;

	return ;
}

