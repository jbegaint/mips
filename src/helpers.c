#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "list.h"

#include "arch/address.h"
#include "arch/section.h"
#include "instructions/instructions.h"
#include "notify.h"

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
	DEBUG_MSG("all registers reset");
	for (int i = 1; i < 36; i++)
		reset_register(arch, i);
}

void reset_register(ARCH arch, int index)
{
	set_register(arch, index, 0);
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
	display_instruction(instr.word, stdout);
}

void print_instruction_bytes(INSTR instr)
{
	for (int i = 0; i < 4; i++)
		printf("%02x ", instr.bytes[3-i]);
}

INSTR get_instr_from_addr(ARCH arch, uint address)
{
	INSTR instr;

	for (int j = 0; j < 4; j++)
		get_byte(arch, address + j, &(instr.bytes[3-j]));

	return instr;
}


/* BYTES */
uint get_bytes_from_addr(ARCH arch, uint address)
{
	INSTR instr;

	instr = get_instr_from_addr(arch, address);

	return instr.word;
}

void set_bytes_from_addr(ARCH arch, uint address, uint value)
{
	INSTR instr;
	int section_index, offset;

	instr.word = value;
	section_index = get_section(arch, address);
	offset = get_offset(arch, address, section_index);

	if (section_index == -1) {
		WARNING_MSG("address %08x not allocated", address);
		return;
	}

	for (int j = 0; j < 4; j++) {
		*((arch->sections)[section_index].data + offset + j) = instr.bytes[3-j];
	}
}


/* DESC */
int get_desc_id(char* desc_name)
{
	for (int i = 0; i < DESC_ARRAY_LENGTH; i++) {
		if (strcmp(desc_name, DESC_ARRAY[i].name) == 0)
			return i;
	}
	return -1;
}
