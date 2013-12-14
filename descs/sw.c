#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"
#include "notify.h"
#include "utils.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"SW $%u, %x($%u)\n", rt, immediate, rs);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	uint val_rs, val_rt;
	uint result, test;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rt = (arch->registers)[rt];
	val_rs = (arch->registers)[rs];
	result = val_rs + immediate;

	test = parser_instr(result , 0, 1);

	if (test != 0)
		print_error("error adrress");
	else
		set_word_from_addr(arch, result, val_rt);
}

