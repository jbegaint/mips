#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "arch/arch.h"
#include "arch/section.h"

#include "parsers.h"
#include "utils.h"

#include "simMips.h"

extern char* REG_NAMES[36];

int parse_hex_value(char* hex_str, uint* hex_value, uint hex_leng)
{
	uint i;

	/* prevent new line bug */
	if (sscanf(hex_str, "%s", hex_str) != 1)
		return 0;

	/* if str begins with 0x, shift it */
	if (strlen(hex_str) > 1) {
		if (*(hex_str) == '0' && *(hex_str+1) == 'x')
			hex_str += 2;
	}

	if (strlen(hex_str) > hex_leng)
		/* invalid address: 32bits, 4 bytes, 8 hex chars */	
		return 0;

	for (i = 0; i < strlen(hex_str); i++) {
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

int parse_addr_value(char* addr_value_str, uint* addr_value)
{
	/* legacy code, specs has changed since */
	/* 8 bits */
	/*return parse_hex_value(addr_value_str, (uint*) addr_value, 2);*/

	/* 32 bits */
	return parse_addr(addr_value_str, addr_value);
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

		if (reg_index < 36 && reg_index >= 0)
			return atoi(reg_str);
		else
			return -1;
	}
	else {
		for (i=0; i < 36; i++) {
			if (strcmp(*(REG_NAMES+i), reg_str) == 0)
				return i;
		}
	}

	return reg_index;
}

int parse_args(struct command* cmd, char* str_arg, char** args)
{
	char* str1, *str2;
	char* token, *subtoken;
	char* found_colon, *found_tild;
<<<<<<< HEAD
	int i;
	int colon_flag = 1, tild_flag = 1;

=======
>>>>>>> 81a88b06e83d13ffb1debf2586daf9c99f20e8b0
	char* delim = " ";
	int i;

	for (i = 0, str1 = str_arg; ; str1 = NULL, i++) {

		if ((token = strtok(str1, delim)) == NULL)
			break;

		*(args+i) = token;

		if ((found_colon = strchr(token, ':')) && strlen(token) > 1) {
			for (str2 = token; ; str2 = NULL, i++) {
				if ((subtoken = strtok(str2, ":")) == NULL) {
 					break;
				}
<<<<<<< HEAD

				if (colon_flag) {
					*(args+i) = subtoken;
					i++;
					*(args+i) = ":";	
					colon_flag = 0;
				}
				else {
					*(args+i) = subtoken;
					colon_flag = 1;
				}
			}
			i--;
		}

		
		if ((found_tild = strchr(token, '~'))) {
=======
				*(args+i) = subtoken;
				*(args+i+1) = ":";
			}
			swap_str(args+i-1, args+i);
		}

		
		if ((found_tild = strchr(token, '~')) && strlen(token) > 1) {
>>>>>>> 81a88b06e83d13ffb1debf2586daf9c99f20e8b0
			for (str2 = token; ; str2 = NULL, i++) {
				if ((subtoken = strtok(str2, "~")) == NULL) {
 					break;
				}
<<<<<<< HEAD

				if (tild_flag) {
					*(args+i) = subtoken;
					i++;
					*(args+i) = "~";	
					tild_flag = 0;
				}
				else {
					*(args+i) = subtoken;
					tild_flag = 1;
				}
			}
			i--;
		}
	}
=======
				*(args+i) = subtoken;
				*(args+i+1) = "~";
			}
			swap_str(args+i-1, args+i);
		}
	}

	fprintf(stderr, "%d\n", i);
>>>>>>> 81a88b06e83d13ffb1debf2586daf9c99f20e8b0

	/* check usage */
	if (i < cmd->min || ( i > cmd->max && cmd->max != -1))
		return 0;

	return 1;
}