#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

void display(uint32_t word)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	fprintf(stdout,"SRL $%u, $%u, $%u\n", rd, rt ,sa);
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rt = (arch->registers)[rt];
	
	(arch->registers)[rd] = val_rt >> sa;

}
