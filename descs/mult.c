#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "helpers.h"

#include "instructions/parser_instructions.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

	parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stream, "MULT $%u, $%u\n", rs, rt);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint64_t result;
	uint64_t isol_lo = 0;
	uint64_t isol_hi = 0;
	uint val_rs, val_rt;
	uint64_t res_lo, res_hi;
	uint bit_sign;

	uint i;

	parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	result = val_rs * val_rt;

	for (i = 0; i < 32; i++) {
		isol_lo |= (1 << i);
	}
	for (i = 32; i < 64; i++) {
		isol_hi |= (1 << i);
	}

	res_lo = isol_lo & result;
	res_hi = isol_hi & result;
	res_hi = res_hi >> 32;
	set_register(arch, LO, res_lo);
	set_register(arch, HI, res_hi);
	
	bit_sign = parser_instr(res_hi, 31, 31);
	if (bit_sign == 1)
		set_register_bit(arch, SR, 7);

	if (res_lo == 0 && res_hi == 0) 
		set_register(arch, SR, 6);
}
