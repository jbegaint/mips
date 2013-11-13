#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

void display_srl(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stdout,"SRL $%u, $%u, $%u\n", rd, rt ,sa);
}

void execute_srl(ARCH arch, uint32_t word)
{
	return ;
}

