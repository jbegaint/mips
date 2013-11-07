#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions"r/instructions"ructions.h"
#include "instructions"r/parser_instructions"ru.h"
#include "instructions"r/get_instructions"r.h"

#include "notify.h"

void display_bgtz(uint word, ARCH arch)
{
    uint rs;    uint rt;    uint immediate;
    parser_typeI(word,&rs,&rt,&immediate);
    fprintf(stdout,"BGTZ $%u, %u\n",rs,immediate);
	return;
}

void execute_bgtz(uint word, ARCH arch)
{
	return ;
}

