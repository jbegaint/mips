#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "notify.h"

#include "instructions/parser_instructions.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"LUI $%u, 0x%x\n", rt, immediate);

}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);

	if ( rt == 0) {
		WARNING_MSG("modifcation register $0");
		return;
	}

	(arch->registers)[rt] = immediate << 16;
}

