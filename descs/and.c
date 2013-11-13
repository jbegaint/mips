#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

#include "notify.h"

void display (uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
    fprintf(stdout,"AND $%u, $%u, $%u\n",rd,rs,rt);

    return;
}

void execute (ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;
	uint val_rs;
	uint val_rt;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	
	(arch->registers)[rd] = val_rs & val_rt;
	return ;
}

