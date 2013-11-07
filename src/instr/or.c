#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"

void display_or(uint word, ARCH arch)
{
    uint rs;    uint rt;    uint rd;    uint sa;    parser_typeR(word,&rs,&rt,&rd,&sa);
    fprintf(stdout,"OR $%u, $%u, $%u\n",rd,rs,rt);

    return;
}

void execute_or(uint word, ARCH arch)
{
	return ;
}

