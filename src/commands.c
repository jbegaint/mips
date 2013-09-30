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
	char* arg;

	arg = strtok(str_arg, " ");

	/* missing argument */
	if (arg == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}

	/* address not in hexa, or negative */
	if (sscanf(arg, "%x", &addr) != 1 || addr < 0) {
		print_error("Invalid address");
		return 0;
	}

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	uint val;
	char* args[2];

	int addr;
	int section_index;
	int offset;


	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}


	addr = parse_addr(args[0]);
	section_index = get_section(arch, addr);

	if (section_index == -1) {
		print_error("address not allocated");
		return CMD_EXIT_FAILURE;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("error parsing memory value");
		return 0;
	}

	/* now we calculate offset in data section */
	offset = addr - (arch->sections)[section_index].start_addr;

	*((arch->sections)[section_index].data + offset) = val;

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lr(ARCH arch, char* str_arg) 
{
	int reg;
	unsigned int val;

	char* args[2];

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("Invalid value");
		return 0;
	}

	reg = parse_register(args[0]);

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
	    	return 0;
	    }

	    display_reg(arch, reg_index);
	    ptr_arg = strtok(NULL, " ");

	}

	return CMD_EXIT_SUCCESS;
}