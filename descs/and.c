#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

#include "notify.h"
#include "helpers.h"

void display (uint32_t word)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
    fprintf(stdout,"AND $%u, $%u, $%u\n", rd, rs, rt);
}

void execute (ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rs, val_rt;
	uint bit_sign;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];
	
	(arch->registers)[rd] = val_rs & val_rt;
	
	bit_sign = parser_instr(val_rs & val_rt, 31, 31);
	if (bit_sign == 1)
		set_register(arch, SR, 64);

	if ( (val_rs & val_rt) == 0) 
		set_register(arch, SR, 32);
}

