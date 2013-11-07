#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions"r/instructions"ructions.h"
#include "instructions"r/parser_instructions"ru.h"
#include "instructions"r/get_instructions"r.h"

#include "notify.h"

void display_j(uint word, ARCH arch)
{
    uint target;    parser_typeJ(word,&target);    fprintf(stdout,"J %u\n",target);    return;
}

void execute_j(uint word, ARCH arch)
{
	return ;
}

