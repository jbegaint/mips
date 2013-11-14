#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "helpers.h"


void display(uint32_t word)
{
    uint target;
    parser_typeJ(word, &target);
    fprintf(stdout,"J %u\n", target);
}

void execute(ARCH arch, uint32_t word)
{
    uint target;
	uint result = 0;
	uint val_PC_fort;

    parser_typeJ(word, &target);
	
	result = target << 2;
	
	val_PC_fort = parser_instr(get_register(arch, PC), 28, 31);
	val_PC_fort = val_PC_fort << 28;
	
	set_register(arch, PC, result + val_PC_fort);

}

