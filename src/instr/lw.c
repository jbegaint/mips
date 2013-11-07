#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"


void display_lw(uint word, ARCH arch)
{
    uint rs;    uint rt;    uint immediate;
    parser_typeI(word,&rs,&rt,&immediate);
    fprintf(stdout,"LW $%u, %u($%u)\n",rt,immediate,rs);
	return;
}

void execute_lw(uint word, ARCH arch)
{
	return ;
}

