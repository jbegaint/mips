#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

#include "helpers.h"


void display (uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stdout,"ADDI $%u, $%u, %u\n", rt, rs, immediate);
}

void execute (ARCH arch, uint32_t word)
{
	uint rs, rt;
    uint immediate, val_rs;
	uint64_t add;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];

	add = val_rs + immediate;

	if (add > 0xFFFFFFFF)
		/* implement set bit sr */
		set_register(arch, SR, 2049);
	else
		(arch->registers)[rt] = add;
}

