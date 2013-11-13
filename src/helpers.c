#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "list.h"

#include "arch/address.h"
#include "instructions/instructions.h"

list_t BP_LIST;

/* BREAKPOINTS */
void set_breakpoint(uint32_t address)
{
	if (get_breakpoint_id(address) == -1)
		BP_LIST = (list_t) add_sort(&address, BP_LIST, sizeof(uint32_t));
}

void del_breakpoint_by_id(int id)
{
	BP_LIST = (list_t) del_elt_n(BP_LIST, id);
}

void del_breakpoint_by_addr(uint32_t address) 
{
	int id;
	if ((id = get_breakpoint_id(address)) != -1)
		del_breakpoint_by_id(id);
}

int get_breakpoint_id(uint32_t address)
{
	return find_elt_int(&address, BP_LIST);
}

void reset_breakpoints(void)
{
	BP_LIST = (list_t) NULL;
}


/* PC */
void set_pc(ARCH arch, uint32_t address)
{
	arch->registers[PC] = address;
}

uint32_t get_pc(ARCH arch)
{
	return arch->registers[PC];
}

/* SECTIONS */
uint32_t get_section_end(ARCH arch, int section_id) 
{
	return arch->sections[section_id].start_addr + arch->sections[section_id].size;
}

/* REGISTERS */
void reset_registers(ARCH arch)
{
	for (int i = 1; i < 36; i++)
		arch->registers[i] = 0;
}

void print_instruction_bytes(INSTR instr)
{
	for (int i = 0; i < 4; i++)
		printf("%02x ", instr.bytes[3-i]);
}

void reset_sr(ARCH arch)
{
	arch->registers[SR] = 0;
}

void set_sr(ARCH arch, uint32_t word)
{
	arch->registers[SR] = word;
}

/* INSTRUCTIONS */
void print_decoded_instruction(ARCH arch, uint32_t address)
{
	INSTR instr;

	for (int j = 0; j < 4; j++)
		get_byte(arch, address + j, &(instr.bytes[3-j]));

	print_instruction_bytes(instr);
	display_instruction(instr.word);
}
