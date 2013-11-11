#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

#include "arch/address.h"
#include "arch/arch.h"
#include "arch/register.h"
#include "arch/section.h"

#include "elf/mipself.h"

#include "commands.h"
#include "helpers.h"
#include "list.h"
#include "notify.h"
#include "parsers.h"
#include "run.h"
#include "simMips.h"
#include "utils.h"

#include "desc/desc.h"
#include "desc/desc_utils.h"


int execute_cmd_ex(ARCH arch, char** args)
{
	UNUSED(arch);
	UNUSED(args);

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

	(arch->regs)[reg] = (uint) val;

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

	    reg_index = parse_register(*(args+i));

	    if (reg_index == -1)
	    	return CMD_EXIT_INVALID_REG;

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

	reset_breakpoints();
	reset_registers(arch);
	state = NOT_STARTED;

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

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (sscanf(args[1], "%d", &instr) != 1) {
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
		/*if (!display_instr(lgn_instr.word)) {
			printf("\n");
			return CMD_EXIT_ERROR;
			WARNING_MSG("no match");
		}*/

		DEBUG_MSG("NOT YET RE-IMPLEMENTED");
	}

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_dm(ARCH arch, char** args)
{
	char* found_colon;
	char* found_tild;

	found_colon = strchr(*args, ':');
	found_tild = strchr(*args, '~');

	if (!found_colon != !found_tild) { 

		if (found_colon) {
			DEBUG_MSG("Execute dm <address>:<bytes_nb>");
			return display_bytes_from_addr(arch, *args);
		} else {
			DEBUG_MSG("Execute dm <address>~<address>");
			return display_addr_to_addr(arch, *args);
		}
	}
	else if (!found_tild && !found_colon) {
		DEBUG_MSG("execute dm <address>");
		return display_one_addr(arch, *args);
	}
	else {
		return CMD_EXIT_FAILURE;
	}

	return CMD_EXIT_SUCCESS;
}


int execute_cmd_di(ARCH arch, char** args)
{
	UNUSED(arch);
	UNUSED(args);

	display_desc_array();
	return CMD_EXIT_SUCCESS;
}

int execute_cmd_ds(ARCH arch, char** args)
{
	UNUSED(args);

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
		run(arch);
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

	set_pc(arch, addr);
	run(arch);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_s(ARCH arch, char** args)
{
	UNUSED(args);

	if (state == FINISHED)
		set_breakpoint(4);
	else
		set_breakpoint(get_pc(arch) + 4);

	run(arch);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_si(ARCH arch, char** args)
{
	UNUSED(args);
	/* stop at next instruction */
	/* if jump, stop at next instruction after jump */
	/* set_breakpoint(jump_adress) ;*/
	set_breakpoint(arch->regs[PC] + 4);

	/* launch run */

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
	if (get_breakpoint_id(addr) != -1) {
		print_error("breakpoint already exists");
		return CMD_EXIT_ERROR;
	}

	set_breakpoint(addr);

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

	if ((id = get_breakpoint_id(addr)) == -1) {
		print_error("breakpoint does not exist");
		return CMD_EXIT_ERROR;
	}

	del_breakpoint_by_id(id);

	fprintf(stdout, "bp at 0x%08x deleted\n", addr);

	return CMD_EXIT_SUCCESS;
}

int execute_cmd_db(ARCH arch, char** args)
{
	UNUSED(arch);
	UNUSED(args);

	/* for i in BP_LIST
		display i + da(i)
	*/

	/* temporary */
	display_list(BP_LIST);

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