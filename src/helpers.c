#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "list.h"

#include "arch/address.h"
#include "instructions/instructions.h"

/* BREAKPOINTS */
void add_breakpoint(ARCH arch, uint address)
{
	if (get_breakpoint_id(arch, address) == -1)
		arch->breakpoints = (list_t) add_sort(&address, arch->breakpoints, sizeof(uint));
}

void del_breakpoint_by_id(ARCH arch, int id)
{
	arch->breakpoints = (list_t) del_elt_n(arch->breakpoints, id);
}

void del_breakpoint_by_addr(ARCH arch, uint address) 
{
	int id;
	if ((id = get_breakpoint_id(arch, address)) != -1)
		del_breakpoint_by_id(arch, id);
}

int get_breakpoint_id(ARCH arch, uint address)
{
	return find_elt_int(&address, arch->breakpoints);
}

void reset_breakpoints(ARCH arch)
{
	arch->breakpoints = (list_t) NULL;
}

void display_breakpoints(ARCH arch)
{
	uint val;
	for (list_t list = arch->breakpoints; !is_list_empty(list); list = list->next) {
		val = *(uint*) list->val;
		printf("%08x  ", val);
		print_decoded_instruction(arch, val);
	}
}

/* SECTIONS */
uint get_section_end(ARCH arch, int section_id) 
{
	return arch->sections[section_id].start_addr + arch->sections[section_id].size;
}

/* REGISTERS */
void reset_registers(ARCH arch)
{
	for (int i = 1; i < 36; i++)
		reset_register(arch, i);
}

void reset_register(ARCH arch, int index)
{
	arch->registers[index] = 0;
}

void set_register(ARCH arch, int index, uint value)
{
	arch->registers[index] = value;
}

uint get_register(ARCH arch, int index)
{
	return arch->registers[index];
}

/* INSTRUCTIONS */
void print_decoded_instruction(ARCH arch, uint address)
{
	INSTR instr;

	for (int j = 0; j < 4; j++)
		get_byte(arch, address + j, &(instr.bytes[3-j]));

	print_instruction_bytes(instr);
	display_instruction(instr.word);
}

void print_instruction_bytes(INSTR instr)
{
	for (int i = 0; i < 4; i++)
		printf("%02x ", instr.bytes[3-i]);
}