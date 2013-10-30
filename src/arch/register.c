#include <stdio.h>

#include "arch/arch.h"
#include "arch/register.h"

#include "parsers.h"
#include "utils.h"

extern char* REG_NAMES[36];

void display_reg_all(ARCH arch) {
	int i;
	
	for (i=1; i <= 36; i++) {
		/* padding */
		if (i != 1)
			printf("  ");

		display_reg(arch, i-1);

	    if (i%4 == 0)
	    	printf("\n");
	}
}

void display_reg(ARCH arch, int reg_index) {

	char* reg_name = REG_NAMES[reg_index];
	uint reg_value = (arch->regs)[reg_index];

	fprintf(stdout, "%s : %08x   ", reg_name, reg_value);
}