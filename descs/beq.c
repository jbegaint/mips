#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word, FILE* stream, ARCH arch)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);

    /*fprintf(stderr, "%08x\n", get_register(arch, PC));*/

    fprintf(stream,"BEQ $%u, $%u, %x", rs, rt, (int16_t)(immediate << 2) + get_register(arch, PC));
    fprintf(stream, "\n");
    /*display_jump_reloc_symbol(arch, (immediate << 2) + get_register(arch, PC));*/
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	uint val_rs, val_rt;
	int32_t target_offset, val_PC;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	if ( val_rs == val_rt ) {
		target_offset = (int16_t) immediate << 2;
		val_PC = get_register(arch, PC);
		set_register(arch, PC, val_PC+target_offset);
	}
}

