#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"
#include "parsers.h"
#include "dr.h"
#include "dm.h"
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

	print_info("Execute testcmd <address>");
	
	if (parse_args(str_arg, args, 1) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	/* address not in hexa, or negative  */
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
	uint val, addr;
	int section_index, offset;
	char* args[2];

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
	uint val;
	char* reg_str = malloc(sizeof(*reg_str));
	char* args[2];

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

int execute_cmd_lp(ARCH arch, char* str_arg)
{
	FILE* f;
	char* args[1];

	if (parse_args(str_arg, args, 1) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	f = open_file(str_arg);

	if (f == NULL) {
		return CMD_EXIT_FAILURE;
	}

	fclose(f);

	print_info("not implemented yet");
	print_info("file closed");

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_da(ARCH arch, char* str_arg)
{
	uint addr;
	int instr, i;

	char* args[2];

	if (parse_args(str_arg, args, 2) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (sscanf(args[0], "%x", &addr) != 1) {
		print_error("Invalid address");
		return CMD_EXIT_FAILURE;
	}

	if (sscanf(args[1], "%d", &instr) != 1) {
		print_error("Invalid instructions number");
		return CMD_EXIT_FAILURE;
	}

	for (i=0; i < instr; i++) {
		printf("%08x\n", addr + 4*i);
	}

	print_info("not implemented yet");

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_dm(ARCH arch, char* str_arg)
{
	char* found_colon;
	char* found_tild;

	found_colon = strchr(str_arg, ':');
	found_tild = strchr(str_arg, '~');

	if (!found_colon != !found_tild) {
		/* xor */	
		if (found_colon) {
			print_info("Execute dm <address>:<nb_bytes>");
		} else {
			return display_addr_to_addr(arch, str_arg);
		}
	}
	else if (!found_tild && !found_colon) {
		return display_one_addr(arch, str_arg);		
	}
	else {
		return CMD_EXIT_FAILURE;
	}

	return CMD_EXIT_SUCCESS;
}
