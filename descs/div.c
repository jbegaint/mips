#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "helpers.h"
#include "instructions/parser_instructions.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stream,"DIV $%u, $%u\n", rs, rt);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint q, reste;
	uint val_rs, val_rt;
	uint bit_sign;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	
	if (val_rt == 0) {
		set_register(arch, SR, 4096);
		WARNING_MSG("Division by zero");
	}
	else {
		q = val_rs / val_rt;
		reste = val_rs % val_rt;
		set_register(arch, HI, q);
		set_register(arch, LO, reste);
		
		bit_sign = parser_instr(q, 31, 31);
		if (bit_sign == 1)
			set_register(arch, SR, 64);
	
		if (q == 0 && reste == 0) 
			set_register(arch, SR, 32);
	}
}
