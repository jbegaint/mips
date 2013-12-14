#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"

void display(uint32_t word, FILE* stream)
{
    uint rs, rt, rd, sa;

    parser_typeR(word, &rs, &rt, &rd, &sa);

   fprintf(stream, "SLLV $%u, $%u, $%u\n", rd, rt, rs); 
}

void execute(ARCH arch, uint32_t word)
{
    uint rs, rt, rd, sa;
	uint val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);

    /* as we do not need sa, let's reuse the variable here */
    sa = (arch->registers)[rs] & 0x5;

    val_rt = (arch->registers)[rt];
    (arch->registers)[rd] = val_rt << sa;
}

