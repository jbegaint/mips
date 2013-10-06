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
	
	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

	/* address not in hexa, or negative  */
	if (sscanf(args[0], "%x", &addr) != 1 || addr < 0)
		return CMD_EXIT_FAILURE;

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	uint addr, tmp_val;
	uchar val;
	int section_index, offset;
	char* args[2];

	if (parse_args(str_arg, args, 2) != 1)
		return CMD_EXIT_MISSING_ARG;	

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	/* tmp_val is uint as C90 does not support hhu */
	if (sscanf(args[1], "%u", &tmp_val) != 1) {
		print_error("Invalid memory value");
		return CMD_EXIT_FAILURE;
	}

	if (tmp_val > 0xFF) {
		print_error("incorrect value");
		return CMD_EXIT_FAILURE;
	}

	val = (uchar) tmp_val;

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
	char* args[2];

	if (parse_args(str_arg, args, 2) != 1)
		return CMD_EXIT_MISSING_ARG;

	reg = parse_register(args[0]);

	if (reg == -1 )
		return CMD_EXIT_INVALID_REG;

	if (!parse_reg_value(args[1], &val)) {
		print_error("invalid register value");
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

	    if (reg_index == -1)
	    	return CMD_EXIT_INVALID_REG;

	    display_reg(arch, reg_index);
	    ptr_arg = strtok(NULL, " ");

	}

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lp(ARCH arch, char* str_arg)
{
	FILE* f;
	char* args[1];

	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

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

	print_info("Execute da");

	if (parse_args(str_arg, args, 2) != 1)
		return CMD_EXIT_MISSING_ARG;

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

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

	print_info("Execute dm");

	found_colon = strchr(str_arg, ':');
	found_tild = strchr(str_arg, '~');

	if (!found_colon != !found_tild) {
		/* xor */	

		if (found_colon) {
			print_info("Execute dm <address>:<bytes_nb>");
			return display_bytes_from_addr(arch, str_arg);

		} else {
			print_info("Execute dm <address>~<address>");
			return display_addr_to_addr(arch, str_arg);
		}
	}
	else if (!found_tild && !found_colon) {
		print_info("execute dm <address>");
		return display_one_addr(arch, str_arg);		
		
	}
	else {
		return CMD_EXIT_FAILURE;
	}

	return CMD_EXIT_SUCCESS;
}
