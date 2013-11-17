#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"BGTZ $%u, %u\n", rs, immediate);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	int32_t target_offset, val_PC, val_rs;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];

	if ( val_rs > 0 ) {
		target_offset = (int16_t) immediate << 2;
		val_PC = get_register(arch, PC);
		set_register(arch, PC, val_PC + target_offset);
	}
}

