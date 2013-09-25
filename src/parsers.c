#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern char* REG_NAMES[32];

int parse_register(char* reg) 
{
	int i;
	int reg_index = -1;

	if (*reg == '$') {
		/* 1 char shift for the '$' */
		reg++;
	}

	if (strlen(reg) == 1 && isdigit(*reg)) {
		return atoi(reg);
	}
	else if (strlen(reg) == 2 && isdigit(reg[0]) && isdigit(reg[1])) {
		return atoi(reg);
	}
	else {
		for (i=0; i < 32; i++) {
			if (strcmp(REG_NAMES[i], reg) == 0) {
				return i;
			}
		}
	}

	return reg_index;
}