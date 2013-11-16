#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"
#include "helpers.h"


void display(uint32_t word)
{
    uint rs, rt, immediate;

    parser_typeI(word, &rs, &rt, &immediate);
    fprintf(stdout,"LW $%u, %u($%u)\n", rt, immediate, rs);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, immediate;
	uint val_rs;
	uint result, test;

    parser_typeI(word, &rs, &rt, &immediate);
	val_rs = (arch->registers)[rs];
	result = val_rs + immediate;

	test = parser_instr(result , 0, 1);
	if ( test != 0 ) {
		WARNING_MSG("error adrress");
	}
	
	else {

		(arch->registers)[rt] = get_bytes_from_addr(arch, result);
	}
}

