#include <stdio.h>

#include "arch/arch.h"
#include "arch/register.h"

#include "parsers.h"
#include "utils.h"

extern char* REG_NAMES[32];

void display_reg_all(ARCH arch) {
	int i;
	
	for (i=0; i < 32; i++) {
		display_reg(arch, i);
	}
}

void display_reg(ARCH arch, int reg_index) {

	char* reg_name = REG_NAMES[reg_index];
	uint reg_value = (arch->regs)[reg_index];

	fprintf(stdout, "$%s : 0x%08x\n", reg_name, reg_value);
}