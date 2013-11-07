#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

void display_sll(uint word, ARCH arch)
{
    uint rs;
    uint rt;
    uint rd;
    uint sa;

    parser_typeR(word,&rs,&rt,&rd,&sa);
    if (rs==0 && rt==0 && rd==0 && sa==0){
        display_nop(word,arch);
    }

	fprintf(stdout,"SLL $%u, $%u, $%u\n",rd,rt,sa);
	return;
}

void execute_sll(uint word, ARCH arch)
{
	return ;
}

