#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions"r/instructions"ructions.h"
#include "instructions"r/parser_instructions"ru.h"
#include "instructions"r/get_instructions"r.h"

#include "notify.h"

void display_div(uint word, ARCH arch)
{
    uint rs;    uint rt;    uint rd;    uint sa;    parser_typeR(word,&rs,&rt,&rd,&sa);
    fprintf(stdout,"DIV $%u, $%u\n",rs,rt);

    return;
}

void execute_div(uint word, ARCH arch)
{
	return ;
}

