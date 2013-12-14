#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "notify.h"
#include "utils.h"

#include "instructions/parser_instructions.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"ORI $%u, $%u, 0x%x\n", rt, rs, immediate);

}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);

	if (rt == 0) {
		print_error("can't modify $zero register");
		return;
	}

	(arch->registers)[rt] = (arch->registers)[rs] || immediate;
}

