#include <stdio.h>

#include "dr.h"
#include "arch.h"
#include "utils.h"
#include "parsers.h"

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

	fprintf(stderr, "$%s : %d\n", reg_name, reg_value);
}