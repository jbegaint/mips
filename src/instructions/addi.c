#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"

#include "helpers.h"


void display (uint32_t word)
{
    uint rs;
    uint rt;
    uint immediate;

    parser_typeI(word,&rs,&rt,&immediate);
    fprintf(stdout,"ADDI $%u, $%u, %u\n",rt,rs,immediate);
	return;
}

void execute (ARCH arch, uint32_t word)
{
	uint rs;
    uint rt;
    uint immediate;
	uint64_t add;

    parser_typeI(word,&rs,&rt,&immediate);

	add = rs + immediate;

	if (add>0xFFFFFFFF) {
		fprintf(stderr,"SR modifie\n");
		set_sr(arch,2049); // modification du bit C (0) et O (11)
		return;
	}
	else {
		(arch->regs)[rt] = add;
	}
	return ;
}

