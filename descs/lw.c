#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"
#include "helpers.h"
#include "utils.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"LW $%u, %u($%u)\n", rt, immediate, rs);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	uint val_rs;
	uint result, test;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];
	result = val_rs + (int16_t) immediate;

	if (rt == 0) {
		print_error("can't modify $zero register");
		return;
	}

	test = parser_instr(result , 0, 1);
	if (test != 0)
		print_error("error address");	
	else
		(arch->registers)[rt] = get_word_from_addr(arch, result);
}

