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
    fprintf(stdout,"DIV $%u, $%u\n",rs,rt);

    return;
}

void execute (ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;
	uint q;
	uint reste;
	uint val_rs;
	uint val_rt;

    parser_typeR(word,&rs,&rt,&rd,&sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	
	if (val_rt == 0) {
		set_SR( arch, 4096);
		WARNING_MSG("Division by zero");
		fprintf(stderr,"SR modify\n");
		return;
	}
	else {
		q = val_rs / val_rt;
		reste = val_rs % val_rt;
		set_HI( arch, q);
		set_LO( arch, reste);
	}
	return ;
}

