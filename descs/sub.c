#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"


void display(uint32_t word)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stdout,"ADD $%u, $%u, $%u\n", rd, rs, rt);


}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rs, unit val_rt;
	uint64_t result;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	result = val_rs - val_rt;
	if ( abs(result) > 0x7FFFFFFF) {
	set_register(arch, SR, 2049);
	}
	else {
	(arch->registers)[rd] = result;
	}


}

