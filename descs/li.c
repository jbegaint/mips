#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "notify.h"
#include "utils.h"

#include "instructions/parser_instructions.h"

/* 
	disclaimer : li is a *pseudo instruction* :

	on 32 bits mips : 
		li $rd, IMMED[15:0] == lui $rd, IMMED[15:0]; ori $rd, $rd, IMMED[15:0]

	as this software does not currently support pseudo instructions.
	li as been implemented as follow.
*/

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stream,"LI $%u, 0x%x\n", rt, immediate);

}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);

	if (rt == 0) {
		print_error("can't modify $zero register");
		return;
	}

	(arch->registers)[rt] = immediate << 16;
	(arch->registers)[rt] = ((arch->registers)[rt] | immediate);

}

