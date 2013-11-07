#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

void display_sw(ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint immediate;

    parser_typeI(word,&rs,&rt,&immediate);
    fprintf(stdout,"SW $%u, %u($%u)\n",rt,immediate,rs);
	return;
}

void execute_sw(ARCH arch, uint32_t word)
{
	return ;
}

