#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"
#include "utils.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stream,"SLT $%u, $%u, $%u\n", rd, rs, rt);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rs, val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	if (rd == 0) {
		print_error("can't modify $zero register");
		return;
	}

	
	if (val_rs < val_rt) {
		(arch->registers)[rd] = 1;
	}
	else {
		(arch->registers)[rd] = 0;
	}
}

