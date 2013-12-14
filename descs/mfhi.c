#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"
#include "utils.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
	uint rs, rt, rd, sa;

	parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stream, "MFHI $%u \n", rd);
}

void execute(ARCH arch, uint32_t word)
{
	uint rs, rt, rd, sa;

	parser_typeR(word, &rs, &rt, &rd, &sa);

	if (rd == 0) {
		print_error("can't modify $zero register");
		return;
	}

	(arch->registers)[rd] = get_register(arch, HI);
}
