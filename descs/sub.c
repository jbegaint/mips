#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "helpers.h"

#include "instructions/parser_instructions.h"
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
    uint rs, rt, rd, sa;
	uint val_rs, val_rt;
	uint64_t result;
	uint bit_sign;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	if (rd == 0) {
		print_error("can't modify $zero register");
		return;
	}


	result = val_rs - val_rt;
	if ( result > (uint32_t)result){
		/* implement set bit sr */
		set_register_bit(arch, SR, 11);
		set_register_bit(arch, SR, 0);

		(arch->registers)[rd] = 0xFFFFFFFF & result;
	}
	else {
		(arch->registers)[rd] = result;

		bit_sign = parser_instr(result, 31, 31);
		if (bit_sign == 1)
			set_register_bit(arch, SR, 7);

		if (result == 0) 
			set_register_bit(arch, SR, 6);
	}
}

