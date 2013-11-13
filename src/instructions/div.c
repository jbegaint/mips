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

    parser_typeR(word,&rs,&rt,&rd,&sa);
	
	if (rt == 0) {
		set_SR( arch, 4096);
		WARNING_MSG("Division by zero");
		fprintf(stderr,"SR modify\n");
		return;
	}
	else {
		q=rs/rt;
		reste = rs%rt;
		set_HI( arch, q);
		set_LO( arch, reste);
	}
	return ;
}

