#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stream,"JR $%u \n", rs);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rs, low;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	low = parser_instr(val_rs, 0, 1);

	if (low != 0) {
		print_error("2 lower bits differ from zero");
	}
	
	set_register(arch, PC, val_rs);
}

