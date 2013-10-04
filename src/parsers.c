#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "address.h"

extern char* REG_NAMES[32];

int parse_addr(char* addr_str, uint* addr) 
{
	uint i;

	/* prevent bug with new line */
	if (sscanf(addr_str, "%s", addr_str) != 1)
		return 0;

	/* if str begins with 0x, shift it */
	if (strlen(addr_str) > 1) {
		if (*(addr_str) == '0' && *(addr_str+1) == 'x') {
			addr_str += 2;
		}
	}

	for (i=0; i < strlen(addr_str); i++) {
		if (!isxdigit(*(addr_str+i)))
			return 0;
	}

	if (sscanf(addr_str, "%x", addr) != 1) {
		return 0;
	}	

	return 1;
}

int parse_reg_value(char* reg_val_str, uint* reg_value) 
{
	return parse_addr(reg_val_str, reg_value);
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
		reg_index = atoi(reg_str);

		if ( reg_index < 32 && reg_index >= 0)
			return atoi(reg_str);
		else
			return -1;
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

int parse_args(char* str_arg, char* args[], int args_len)
{
	int i = 0;

	args[0] = strtok(str_arg, " :~");

	if (args[0] == NULL) {
		return -1;
	}

	for (i=1; i < args_len; i++) {
		args[i] = strtok(NULL, " :~");

		if (args[i] == NULL) {
			return -1;
		}
	}

	return 1;
}