#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"
#include "parsers.h"
#include "dr.h"
#include "address.h"

/*
	strtok
	char *strtok(char *str, const char *delim);
	return ptr to next token or NULL 

*/

int parse_args(char* str_arg, char* args[], int args_len)
{
	int i = 0;

	args[0] = strtok(str_arg, " ");

	if (args[0] == NULL) {
		return -1;
	}

	for (i=1; i < args_len; i++) {
		args[i] = strtok(NULL, " ");

		if (args[i] == NULL) {
			return -1;
		}
	}

	return 1;
}


int execute_cmd_ex(ARCH arch)
{
	return quit(arch);
}

int execute_cmd_testcmd(char* str_arg)
{
	int addr;
	
	/*char* arg;*/

	char* args[1];
	
	if ( parse_args(str_arg, args, 1) != 1) {
		print_error("missing argqqs");
		return CMD_EXIT_FAILURE;
	}

	/*arg = strtok(str_arg, " ");*/

	/* missing argument */
	/*if (arg == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}*/

	/* address not in hexa, or negative */
	if (sscanf(args[0], "%x", &addr) != 1 || addr < 0) {
		print_error("Invalid address");
		return 0;
	}

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	char* args[2];
	uint val, addr;
	int section_index, offset;

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("error parsing memory value");
		return CMD_EXIT_FAILURE;
	}

	if (sscanf(args[0], "%x", &addr) != 1) {
		print_error("error parsing addr");
		return CMD_EXIT_FAILURE;
	}

	section_index = get_section(arch, addr);

	if (section_index == -1) {
		return CMD_EXIT_FAILURE;
	}

	/* now we calculate offset in data section */
	offset = get_offset(arch, addr, section_index);

	*((arch->sections)[section_index].data + offset) = val;

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lr(ARCH arch, char* str_arg) 
{
	int reg;
	unsigned int val;
	char* args[2];
	char* reg_str = malloc(sizeof(*reg_str));

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("Invalid value");
		return 0;
	}


	if (sscanf(args[0], "%s", reg_str) != 1) {
		print_error("Invalid value");
		return 0;
	}

	reg = parse_register(reg_str);

	if (reg == -1 ) {
		print_error("register does not exist");
		return 0;
	}

	(arch->regs)[reg] = (uint) val;

	return CMD_EXIT_SUCCESS;

}
int execute_cmd_dr(ARCH arch, char *str_arg) {

	char* ptr_arg;
	int reg_index;

	ptr_arg = strtok(str_arg, " ");

	if (ptr_arg == NULL) {
		display_reg_all(arch);
		return CMD_EXIT_SUCCESS;
	}

	while (ptr_arg != NULL) {
	    reg_index = parse_register(ptr_arg);

	    if (reg_index == -1) {
			print_error("register does not exist");
	    	return CMD_EXIT_FAILURE;
	    }

	    display_reg(arch, reg_index);
	    ptr_arg = strtok(NULL, " ");

	}

	return CMD_EXIT_SUCCESS;
}