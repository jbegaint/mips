#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"

void display_jal(uint word, ARCH arch)
{
    uint target;    parser_typeJ(word,&target);    fprintf(stdout,"JAL %u\n",target);    return;
}

void execute_jal(uint word, ARCH arch)
{
	return ;
}

