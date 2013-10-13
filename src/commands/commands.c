#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch.h"
#include "commands.h"
#include "commands/dm.h"
#include "commands/dr.h"
#include "commands/lm.h"
#include "notify.h"
#include "parsers.h"
#include "utils.h"

int execute_cmd_ex(ARCH arch)
{
	return quit(arch);
}

int execute_cmd_testcmd(char* str_arg)
{
	int addr;
	char* args[1];

	DEBUG_MSG("Execute testcmd <address>");
	
	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

	/* address not in hexa, or negative  */
	if (sscanf(args[0], "%x", &addr) != 1 || addr < 0)
		return CMD_EXIT_FAILURE;

	DEBUG_MSG("<address> = 0x%x", addr);	

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	uint addr = 600;
	uchar val;
	int section_index, offset;
	char* args[2];

	DEBUG_MSG("Execute lm <address> <addr_value>");

	if (parse_args(str_arg, args, 2) != 1)
		return CMD_EXIT_MISSING_ARG;	
	
	if (!parse_addr_value(args[1], &val))
		return CMD_EXIT_INVALID_ADDR_VALUE;

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;


	section_index = get_section(arch, addr);

	if (section_index == -1)
		return CMD_EXIT_FAILURE;

	offset = get_offset(arch, addr, section_index);

	*((arch->sections)[section_index].data + offset) = val;

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lr(ARCH arch, char* str_arg) 
{
	int reg;
	uint val;
	char* args[2];

	DEBUG_MSG("Execute lr <register> <reg_value>");

	if (parse_args(str_arg, args, 2) != 1)
		return CMD_EXIT_MISSING_ARG;

	reg = parse_register(args[0]);

	if (reg == -1 )
		return CMD_EXIT_INVALID_REG;

	if (!parse_reg_value(args[1], &val)) {
		return CMD_EXIT_INVALID_REG_VALUE;
	}

	(arch->regs)[reg] = (uint) val;

	return CMD_EXIT_SUCCESS;

}
int execute_cmd_dr(ARCH arch, char *str_arg) {

	char* ptr_arg;
	int reg_index;

	DEBUG_MSG("Execute dr <register>");

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

	DEBUG_MSG("Execute lp <elf_file>");

	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

	f = open_file(str_arg);

	if (f == NULL) {
		return CMD_EXIT_FAILURE;
	}

	fclose(f);

	WARNING_MSG("not implemented yet");
	DEBUG_MSG("file closed");

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_da(ARCH arch, char* str_arg)
{
	uint addr;
	int instr, i;

	char* args[2];

	DEBUG_MSG("Execute da <addr> <instr>");

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

	WARNING_MSG("not implemented yet");

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
			DEBUG_MSG("Execute dm <address>:<bytes_nb>");
			return display_bytes_from_addr(arch, str_arg);

		} else {
			DEBUG_MSG("Execute dm <address>~<address>");
			return display_addr_to_addr(arch, str_arg);
		}
	}
	else if (!found_tild && !found_colon) {
		DEBUG_MSG("execute dm <address>");
		return display_one_addr(arch, str_arg);		
		
	}
	else {
		return CMD_EXIT_FAILURE;
	}

	return CMD_EXIT_SUCCESS;
}
