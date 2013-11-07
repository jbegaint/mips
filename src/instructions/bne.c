#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

void display_bne(ARCH arch, uint32_t word)
{
    uint rs;
    uint rt;
    uint immediate;

    parser_typeI(word,&rs,&rt,&immediate);
    fprintf(stdout,"BNE $%u, $%u, %u\n",rs,rt,immediate);
	return;
}

void execute_bne(ARCH arch, uint32_t word)
{
	return ;
}

