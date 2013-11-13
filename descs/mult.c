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
	uint val_rs;
	uint val_rt;
	uint res_lo;
	uint res_hi;

    uint i;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	result = val_rs * val_rt;

    for (i=0; i<32; i++){
        isol_lo |= (1<<i) ;
    }
    for (i=32; i<64; i++){
        isol_hi |= (1<<i) ;
    }
	
	res_lo = isol_lo & result;
	res_hi = isol_hi & result;
	res_hi = res_hi >> 32;
	set_LO(arch, res_lo);
	set_HI(arch, res_hi);
	
	return ;
}

