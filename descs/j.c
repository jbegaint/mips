#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"


void display (uint32_t word)
{
    uint target;
    parser_typeJ(word,&target);
    fprintf(stdout,"J %u\n",target);
    return;
}

void execute (ARCH arch, uint32_t word)
{
	return ;
}

