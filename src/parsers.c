#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"

extern char* REG_NAMES[32];

int parse_addr(ARCH arch, char* addr_str) {

	uint addr;
	int i;
	SECTION* section_ptr;

	if (sscanf(addr_str, "%u", &addr) != 1) {
		print_error("error parsing addr");
		return -1;
	}

	/* find in which section is addr located*/

	for (i=0; i < 3; i++) {
		section_ptr = &(arch->sections[i]);
		if ( addr >= section_ptr->start_addr && addr <= section_ptr->start_addr + section_ptr->size) {
			return i;
		}
	}

	return -1;
}


int parse_register(char* reg_str) 
{
	int i;
	int reg_index = -1;

	if (*reg_str == '$') {
		/* 1 char shift for the '$' character */
		reg_str++;
	}

	if (strlen(reg_str) == 1 && isdigit(*reg_str)) {
		return atoi(reg_str);
	}
	else if (strlen(reg_str) == 2 && isdigit(reg_str[0]) && isdigit(reg_str[1])) {
		return atoi(reg_str);
	}
	else {
		for (i=0; i < 32; i++) {
			if (strcmp(REG_NAMES[i], reg_str) == 0) {
				return i;
			}
		}
	}

	return reg_index;
}