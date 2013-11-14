#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"

void display(uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stdout,"BNE $%u, $%u, %u\n", rs, rt, immediate);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	uint val_rs, val_rt;
	uint target_offset, val_PC;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	if ( val_rs != val_rt ) {
		target_offset = immediate << 2;
		val_PC = get_register(arch, PC);
		set_register(arch, PC, val_PC+target_offset);
	}
}

