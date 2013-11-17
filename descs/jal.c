#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word, FILE* stream)
{
    uint target;
    parser_typeJ(word, &target);
    fprintf(stream,"JAL %u\n", target);
}

void execute(ARCH arch, uint32_t word)
{
    uint target;
	uint result = 0;
	uint val_PC, val_PC_fort;

    parser_typeJ(word, &target);
	val_PC = get_register(arch, PC);
	(arch->registers)[31] = val_PC + 4; 
	/* should be +8 but was already incremented before execution */
	
	result = target << 2;
	
	val_PC_fort = parser_instr(val_PC, 28, 31);
	val_PC_fort = val_PC_fort << 28;
	
	set_register(arch, PC, result + val_PC_fort);
}

