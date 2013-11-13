#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"
#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word)
{
    uint rs, rt, rd, sa;
    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stdout,"ADD $%u, $%u, $%u\n",rd,rs,rt);
}

void execute(ARCH arch, uint32_t word)
{
	uint64_t addi;
    uint rs, rt, rd, sa;
	uint val_rs, val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	addi = val_rs + val_rt;
	
	if (addi > 0xFFFFFFFF)
		set_register(arch, PC, 2049);
	else
		(arch->registers)[rd] = addi;
}

