#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);

    if (rs == 0 && rt == 0 && rd == 0 && sa == 0)
        fprintf(stream, "NOP\n");
    else 
	   fprintf(stream, "SLL $%u, $%u, $%u\n", rd, rt, sa); 
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);

    if (!(rs == 0 && rt == 0 && rd == 0 && sa == 0)) {
        val_rt = (arch->registers)[rt];
		(arch->registers)[rd] = val_rt << sa;
    }
}

