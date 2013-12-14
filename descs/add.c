#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"
#include "instructions/parser_instructions.h"
#include "helpers.h"
#include "notify.h"
#include "utils.h"


void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;
    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stream,"ADD $%u, $%u, $%u\n", rd, rs, rt);
}

void execute(ARCH arch, uint32_t word)
{
	uint64_t addi;
    uint rs, rt, rd, sa;
	uint val_rs, val_rt;
	uint bit_sign;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	
	if (rd == 0) {
		print_error("can't modify $zero register");
		return;
	}

	addi = (uint64_t) val_rs + (uint64_t) val_rt;
		
	if ((uint32_t) addi == 0) {
		set_register_bit(arch, SR, 6);
	}
	else if (addi > (uint32_t) addi) {
		print_info("Overflow");

		set_register_bit(arch, SR, 11);
		set_register_bit(arch, SR, 0);

	}
	else {
		(arch->registers)[rd] = addi;

		bit_sign = parser_instr(addi, 31, 31);

		if (bit_sign == 1)
			set_register_bit(arch, SR, 7);
	}
}

