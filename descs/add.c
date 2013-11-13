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
    uint rd;
    uint sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
    fprintf(stdout,"ADD $%u, $%u, $%u\n",rd,rs,rt);

    return;
}

void execute (ARCH arch, uint32_t word)
{
	uint64_t addi;
    uint rs;
    uint rt;
    uint rd;
    uint sa;
	uint val_rs;
	uint val_rt;

    parser_typeR(word, &rs, &rt, &rd, &sa);
	val_rs = (arch->registers)[rs];
	val_rt = (arch->registers)[rt];

	addi = val_rs + val_rt;
	if (addi>0xFFFFFFFF) {
		fprintf(stderr,"SR modifie\n");
		set_sr(arch,2049); // modification du bit C (0) et O (11)
		return;
	}
	else {
		(arch->registers)[rd] = addi;
	}
	return ;
}

