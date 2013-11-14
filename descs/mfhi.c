#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word)
{
	uint rs, rt, rd, sa;

	parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stdout, "MFHI $%u \n", rd);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	parser_typeR(word, &rs, &rt, &rd, &sa);
	(arch->registers)[rd] = get_register(arch, HI);
}
