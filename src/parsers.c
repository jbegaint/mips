#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "lm.h"

extern char* REG_NAMES[32];

int parse_hex_value(char* hex_str, uint* hex_value, uint hex_leng)
{
	uint i;

	/* prevent new line bug */
	if (sscanf(hex_str, "%s", hex_str) != 1)
		return 0;

	/* if str begins with 0x, shift it */
	if (strlen(hex_str) > 1) {
		if (*(hex_str) == '0' && *(hex_str+1) == 'x') {
			hex_str += 2;
		}
	}

	if (strlen(hex_str) > hex_leng)
		/* invalid address: 32bits, 4 bytes, 8 hex chars */	
		return 0;

	for (i=0; i < strlen(hex_str); i++) {
		if (!isxdigit(*(hex_str+i)))
			return 0;
	}

	if (sscanf(hex_str, "%x", hex_value) != 1) {
		return 0;
	}	

	return 1;
}

int parse_addr(char* addr_str, uint* addr) 
{
	/* 32 bits */
	return parse_hex_value(addr_str, addr, 8);
}

int parse_reg_value(char* reg_val_str, uint* reg_value) 
{
	/* 32 bits */
	return parse_addr(reg_val_str, reg_value);
}

int parse_addr_value(char* addr_value_str, uchar* addr_value)
{
	/* 8 bits */
	return parse_hex_value(addr_value_str, (uint*) addr_value, 2);
}

int parse_register(char* reg_str) 
{
	int i;
	int reg_index = -1;

	/* prevent new line bug */
	if (sscanf(reg_str, "%s", reg_str) != 1)
		return 0;

	if (*reg_str == '$') {
		/* + 1 char shift for the '$' character */
		reg_str++;
	}

	if (strlen(reg_str) == 1 && isdigit(*reg_str)) {
		return atoi(reg_str);
	}
	else if (strlen(reg_str) == 2 && isdigit(*reg_str) && isdigit(*(reg_str+1))) {
		reg_index = atoi(reg_str);

		if (reg_index < 32 && reg_index >= 0)
			return atoi(reg_str);
		else
			return -1;
	}
	else {
		for (i=0; i < 32; i++) {
			if (strcmp(*(REG_NAMES+i), reg_str) == 0) {
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