#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instr/instructions.h"
#include "instr/parser_instru.h"
#include "instr/get_instr.h"

#include "notify.h"

void display_syscall(uint word, ARCH arch)
{
    fprintf(stdout,"SYSCALL");
	return ;
}

void execute_syscall(uint word, ARCH arch)
{
	return ;
}

