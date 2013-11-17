#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"
#include "instructions/parser_instructions.h"
#include "helpers.h"


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

	addi = val_rs + val_rt;
	
	if (addi > (uint32_t) addi) {
		set_register(arch, SR, 2049);
	}
	else {
		(arch->registers)[rd] = addi;

		bit_sign = parser_instr(addi, 31, 31);
		if (bit_sign == 1)
			set_register(arch, SR, 64);
		
		if (addi == 0) 
			set_register(arch, SR, 32);
	}
}

