#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"
#include "helpers.h"
#include "utils.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"ADDI $%u, $%u, %u\n", rt, rs, immediate);
}

void execute(ARCH arch, uint32_t word)
{
	uint rs, rt;
    uint immediate, val_rs;
	uint64_t add;
	uint bit_sign;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];

	if (rt == 0) {
		print_error("can't modify $zero register");
		return;
	}

	add = (uint64_t) val_rs + (uint64_t) immediate;

	if ((uint32_t) add == 0) {
		set_register_bit(arch, SR, 6);
	}
	else if ((uint64_t) add > (uint32_t) add) {
		print_info("Overflow");

		set_register_bit(arch, SR, 11);
		set_register_bit(arch, SR, 0);

	}
	else {
		(arch->registers)[rt] = add;

		bit_sign = parser_instr(add, 31, 31);
		if (bit_sign == 1)
			set_register_bit(arch, SR, 7);
	}
}

