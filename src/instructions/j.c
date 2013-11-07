#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"

void display_j(uint word, ARCH arch)
{
    uint target;    parser_typeJ(word,&target);    fprintf(stdout,"J %u\n",target);    return;
}

void execute_j(uint word, ARCH arch)
{
	return ;
}

