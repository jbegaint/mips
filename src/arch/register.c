#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "arch/register.h"

#include "parsers.h"
#include "utils.h"

char *REG_NAMES[36] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra", "HI", "LO", "SR", "PC"};


void display_reg_all(ARCH arch)
{
	int i;

	for (i = 0; i < 36; i++) {
		display_reg(arch, i);

		if ((i+1) % 4 == 0)
			printf("\n");
		/* padding */
	}
}

void display_reg(ARCH arch, int reg_index)
{
	char *reg_name = REG_NAMES[reg_index];
	uint reg_value = (arch->regs)[reg_index];

	fprintf(stdout, "%4s : %08x   ", reg_name, reg_value);
}
