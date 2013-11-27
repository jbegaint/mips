#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stream,"SRL $%u, $%u, $%u\n", rd, rt ,sa);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
    uint val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rt = (arch->registers)[rt];

	if ( rd == 0) {
		WARNING_MSG("modifcation register $0");
		return;
	}

	
	(arch->registers)[rd] = val_rt >> sa;
}

