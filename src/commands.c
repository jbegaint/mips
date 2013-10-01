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


int execute_cmd_ex(ARCH arch)
{
	return quit(arch);
}

int execute_cmd_testcmd(char* str_arg)
{
	int addr;
	char* args[1];
	
	if (parse_args(str_arg, args, 1) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}


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

	if (parse_args(str_arg, args, 2) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[0], "%x", &addr) != 1) {
		print_error("Invalid address");
		return CMD_EXIT_FAILURE;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("Invalid memory value");
		return CMD_EXIT_FAILURE;
	}


	section_index = get_section(arch, addr);

	if (section_index == -1) {
		return CMD_EXIT_FAILURE;
	}

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

	if (parse_args(str_arg, args, 2) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[0], "%s", reg_str) != 1) {
		print_error("Invalid register");
		return CMD_EXIT_FAILURE;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("Invalid value");
		return CMD_EXIT_FAILURE;
	}

	reg = parse_register(reg_str);

	if (reg == -1 ) {
		print_error("Register does not exist");
		return CMD_EXIT_FAILURE;
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
			print_error("Register does not exist");
	    	return CMD_EXIT_FAILURE;
	    }

	    display_reg(arch, reg_index);
	    ptr_arg = strtok(NULL, " ");

	}

	return CMD_EXIT_SUCCESS;
}