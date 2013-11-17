#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

#include "arch/address.h"
#include "arch/arch.h"
#include "arch/register.h"
#include "arch/section.h"

#include "commands.h"

#include "desc/desc.h"
#include "desc/desc_utils.h"

#include "elf/mipself.h"

#include "instructions/instructions.h"

#include "helpers.h"
#include "list.h"
#include "notify.h"
#include "parsers.h"
#include "run.h"
#include "simMips.h"
#include "utils.h"


int execute_cmd_ex()
{
	DEBUG_MSG("Bye Dave");
	return CMD_QUIT;
}

int execute_cmd_testcmd(ARCH arch, char** args)
{
	uint addr;
	UNUSED(arch);

	DEBUG_MSG("Execute testcmd <address>");

	/* address not in hexa, or negative  */
	if (sscanf(args[0], "%x", &addr) != 1)
		return CMD_EXIT_FAILURE;

	DEBUG_MSG("<address> = 0x%x", addr);

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lm(ARCH arch, char** args)
{
	INSTR val;
	int i = 0;
	int section_index, offset;
	uint addr;

	DEBUG_MSG("Execute lm <address> <addr_value>");

	if (!parse_addr_value(args[1], &val.word))
		return CMD_EXIT_INVALID_ADDR_VALUE;

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	section_index = get_section(arch, addr);

	if (section_index == -1)
		return CMD_EXIT_FAILURE;

	offset = get_offset(arch, addr, section_index);

	for (i = 0; i < 4; i++) {
		*((arch->sections)[section_index].data + offset + i) = val.bytes[i];
	}

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lr(ARCH arch, char** args)
{
	int reg;
	uint val;

	DEBUG_MSG("Execute lr <register> <reg_value>");

	reg = parse_register(args[0]);

	if (reg == -1 )
		return CMD_EXIT_INVALID_REG;
	else if (reg == 0) {
		print_error("$zero can't be modified");
		return CMD_EXIT_INVALID_REG;
	}
	else if (reg >= 32) {
		return CMD_EXIT_INVALID_REG;
	}

	if (!parse_reg_value(args[1], &val)) {
		return CMD_EXIT_INVALID_REG_VALUE;
	}

	(arch->registers)[reg] = (uint) val;

	return CMD_EXIT_SUCCESS;

}
int execute_cmd_dr(ARCH arch, char** args) {

	int reg_index;
	int i = 0;

	DEBUG_MSG("Execute dr <register>");

	if (*args == NULL) {
		display_reg_all(arch);
		return CMD_EXIT_SUCCESS;
	}

	while (*(args+i) != NULL) {

		DEBUG_MSG("parsing register: %s", *(args+i));

	    reg_index = parse_register(*(args+i));

	    if (reg_index == -1) {
	    	printf("\n"); /* clear output */
	    	return CMD_EXIT_INVALID_REG;
		}

	    display_reg(arch, reg_index);

	    if ((i+1)%4 == 0)
	    	printf("\n");
	    i++;
	}

	/* if last row not full */
	if (i%4 != 0)
		printf("\n");

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_lp(ARCH arch, char** args)
{
	FILE* f;
	int res;

	DEBUG_MSG("Execute lp <elf_file>");

	/* rm new line if any */
	if (sscanf(args[0], "%s", args[0]) != 1)
		return CMD_EXIT_FAILURE;

	f = open_file(args[0]);
	if (f == NULL)
		return CMD_EXIT_FILE_NOT_FOUND;
	fclose(f);
	DEBUG_MSG("file closed");

	reset_breakpoints(arch);
	reset_registers(arch);
	arch->state = NOT_STARTED;

	res = mipsloader(args[0],  &(arch->sections[TEXT]), &(arch->sections[DATA]), &(arch->sections[BSS]));

	if (res != 0)
		return CMD_EXIT_FAILURE;

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_da(ARCH arch, char** args)
{

	INSTR lgn_instr;
	int instr, i, j;
	uint addr;

	DEBUG_MSG("Execute da <addr>:<instr>");

	if (*(args+1) == NULL)
		return CMD_EXIT_ERROR;

	if (strcmp(*(args+1), ":") != 0) {
		DEBUG_MSG("usage error");
		return CMD_EXIT_ERROR;
	}


	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (sscanf(args[2], "%d", &instr) != 1) {
		print_error("Invalid instructions number");
		return CMD_EXIT_FAILURE;
	}

	if ( addr < arch->sections[TEXT].start_addr ||
		addr >= arch->sections[TEXT].size + arch->sections[TEXT].start_addr) {
		print_error("address not in .text");
		return CMD_EXIT_ERROR;
	}

	if (addr%4 != 0) {
		print_error("address does not start an instruction");
		return CMD_EXIT_ERROR;
	}

	for (i = 0; i < instr; i++) {
		for (j = 0; j < 4; j++) {

			if (get_byte(arch, addr + 4*i + j, &(lgn_instr.bytes[3-j])) == BYTE_NOT_ALLOCATED)
				return CMD_EXIT_SUCCESS;

			if (j == 0)
				printf("%08x: ", addr + 4*i);

			display_byte(arch, addr + 4*i + j);
		}
	
		if (!display_instruction(lgn_instr.word, stdout)) {
			printf("\n");
			WARNING_MSG("no match");
			return CMD_EXIT_ERROR;
		}
	}

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_dm(ARCH arch, char** args)
{
	/* case ~ or : */
	if ((*(args+2) != NULL) && (*(args+1) != NULL)) {
		
		if (strcmp(*(args+1), ":") == 0) {
			DEBUG_MSG("Execute dm <address>:<bytes_nb>");
			return display_bytes_from_addr(arch, args);
		}
		else if (strcmp(*(args+1), "~") == 0) {
			DEBUG_MSG("Execute dm <address>~<address>");
			return display_addr_to_addr(arch, args);
		}
		else {
			return CMD_EXIT_ERROR;
		}
	}
	else if (*(args+1) == NULL) {
		DEBUG_MSG("execute dm <address>");
		return display_one_addr(arch, args);
	}
	else {
		return CMD_EXIT_ERROR;
	}
}


int execute_cmd_di()
{
	display_desc_array();
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_ds(ARCH arch)
{
	for (int i = 0; i < 3; i++) {
		printf("Section: %s\n", arch->sections[i].name);
		printf("Start address: %0x\n", arch->sections[i].start_addr);
		printf("Size: %d\n", arch->sections[i].size);
		printf("\n");
	}
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_run(ARCH arch, char** args)
{
	uint32_t addr;

	DEBUG_MSG("Execute run [address]");

	if (*args == NULL) {
		run(arch, 0);
		return CMD_EXIT_SUCCESS;
	}

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (addr >= arch->sections[TEXT].start_addr + arch->sections[TEXT].size) {
		print_error("address not in text");
		return CMD_EXIT_INVALID_ADDR;
	}

	/* check if addr is a correct instruction address */
	if (addr%4 != 0) {
		print_error("address does not start an instruction");
		return CMD_EXIT_INVALID_ADDR;
	}

	set_register(arch, PC, addr);
	run(arch, 0);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_s(ARCH arch)
{
	if (arch->state == FINISHED)
		add_breakpoint(arch, 4);
	else
		add_breakpoint(arch, get_register(arch, PC) + 4);

	run(arch, 0);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_si(ARCH arch)
{
	/* stop at next instruction */
	/* if jump, stop at next instruction after jump */
	/* add_breakpoint(jump_adress) ;*/
	
	if (arch->state == FINISHED)
		add_breakpoint(arch, 4);

	run(arch, 1);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_bp(ARCH arch, char** args)
{
	uint32_t addr;

	DEBUG_MSG("Execute bp <address>");

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (addr >= arch->sections[TEXT].start_addr + arch->sections[TEXT].size) {
		print_error("address not in text");
		return CMD_EXIT_INVALID_ADDR;
	}

	/* check if addr is a correct instruction address */
	if (addr%4 != 0) {
		print_error("address does not start an instruction");
		return CMD_EXIT_INVALID_ADDR;
	}

	/* check if bp already in list */
	if (get_breakpoint_id(arch, addr) != -1) {
		print_error("breakpoint already exists");
		return CMD_EXIT_ERROR;
	}

	add_breakpoint(arch, addr);

	fprintf(stdout, "bp at 0x%08x added\n", addr);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_er(ARCH arch, char** args)
{
	uint32_t addr;
	int id;

	DEBUG_MSG("Execute bp <address>");

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (addr > (arch->sections[TEXT].start_addr + arch->sections[TEXT].size)) {
		print_error("address not in text");
		return CMD_EXIT_INVALID_ADDR;
	}

	if ((addr%4) != 0) {
		print_error("address does not start an instruction");
		return CMD_EXIT_INVALID_ADDR;
	}

	if ((id = get_breakpoint_id(arch, addr)) == -1) {
		print_error("breakpoint does not exist");
		return CMD_EXIT_ERROR;
	}

	del_breakpoint_by_id(arch, id);

	fprintf(stdout, "bp at 0x%08x deleted\n", addr);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_db(ARCH arch)
{
	fprintf(stdout, "breakpoints\n");
	
	if (is_list_empty(arch->breakpoints))
		return CMD_EXIT_SUCCESS;

	display_breakpoints(arch);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_help(ARCH arch, char** args)
{
	UNUSED(arch);
	struct command* command;

	if (*args == NULL) {
		print_help_all();
		return CMD_EXIT_SUCCESS;
	}

	command = find_cmd(args[0]);
	if (command == NULL)
		return CMD_NOT_FOUND;

	print_help(command);
	return CMD_EXIT_SUCCESS;
}