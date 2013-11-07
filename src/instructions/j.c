#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"


#include "notify.h"

void display_j(ARCH arch, uint32_t word)
{
    uint target;
    parser_typeJ(word,&target);
    fprintf(stdout,"J %u\n",target);
    return;
}

void execute_j(ARCH arch, uint32_t word)
{
	return ;
}

