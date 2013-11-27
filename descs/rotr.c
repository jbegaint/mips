#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	fprintf(stream,"ROTR $%u, $%u, $%u\n",rd,rt,sa);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;

	uint32_t isol_high = 0;
	uint32_t isol_low = 0;
	uint32_t val_rt;
    uint i;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	val_rt = (arch->registers)[rt];

	if ( rd == 0) {
		WARNING_MSG("modifcation register $0");
		return;
	}


    for (i = 0; i < sa; i++){
        isol_low |= (1<<i) ;
    }
    for (i = sa; i < 32; i++){
        isol_high |= (1<<i) ;
    }

	isol_high = isol_high & val_rt;
	isol_low = isol_low & val_rt;
	isol_high = isol_high >> (32-sa);
	isol_low = isol_low << sa;

	(arch->registers)[rd] = isol_low | isol_high;
}

