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
		val = *(uint *) list->val;
		printf("%08x  ", val);
		print_decoded_instruction(arch, val);
	}

	printf("\n");
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

void set_register_bit(ARCH arch, int reg_index, int bit_index)
{
	uint val;

	val = get_register(arch, reg_index);
	val |= (1 << bit_index);
	set_register(arch, reg_index, val);
}

int get_register_bit(ARCH arch, int reg_index, int bit_index)
{
	int bit;

	bit = get_register(arch, reg_index) & (1 << bit_index);
	return bit;
}

/* INSTRUCTIONS */
void print_decoded_instruction(ARCH arch, uint address)
{
	INSTR instr;

	instr = get_instr_from_addr(arch, address);

	print_instruction_bytes(instr);
	display_instruction(arch, instr.word, stdout);
}

void print_instruction_bytes(INSTR instr)
{
	for (int i = 0; i < 4; i++)
		printf("%02x ", instr.bytes[3 - i]);
}

INSTR get_instr_from_addr(ARCH arch, uint address)
{
	INSTR instr;

	for (int j = 0; j < 4; j++)
		get_byte(arch, address + j, &(instr.bytes[3 - j]));

	return instr;
}

/* BYTES */
uint get_word_from_addr(ARCH arch, uint address)
{
	INSTR instr;

	instr = get_instr_from_addr(arch, address);

	return instr.word;
}

void set_word_from_addr(ARCH arch, uint address, uint value)
{
	int section_index, offset;

	section_index = get_section(arch, address);
	offset = get_offset(arch, address, section_index);

	if (section_index == -1) {
		WARNING_MSG("address %08x not allocated", address);
		return;
	}

	set_word((arch->sections)[section_index].data + offset, value);
}

uint get_word(unsigned char *data)
{
	word_t w;

	for (int j = 0; j < 4; j++)
		w.bytes[3 - j] = *(data + j);

	return w.word;
}

void set_word(unsigned char *data, uint value)
{
	word_t w;

	w.word = value;
	for (int j = 0; j < 4; j++) 
		*(data + j) = w.bytes[3 - j];
}

/* DESC */
int get_desc_id(char *desc_name)
{
	for (int i = 0; i < DESC_ARRAY_LENGTH; i++) {
		if (strcmp(desc_name, DESC_ARRAY[i].name) == 0)
			return i;
	}
	return -1;
}

char* get_symbol_name(ARCH arch, uint addr)
{
	/* 6 offset, as the first symbol concern sections */
	for (uint l = 6; l < arch->SymbolNum; l++) {

		/* check if correct addr and is in section text */
		if (addr == (arch->SymbolTable + l)->st_value 
				&& (arch->SymbolTable + l)->st_shndx == 1) {
			return getName((arch->SymbolTable + l)->st_name);
		}
	}

	return NULL;
}

void display_reloc_symbol(ARCH arch, uint addr)
{
	char* symbol_name;

	symbol_name = get_symbol_name(arch, addr);

	if (symbol_name)
		fprintf(stdout, "\n<%s>:\n", symbol_name);
}

void display_jump_reloc_symbol(ARCH arch, uint addr)
{
	char* symbol_name;

	symbol_name = get_symbol_name(arch, addr);

	if (symbol_name)
		fprintf(stdout, " <%s>\n", symbol_name);
	else
		fprintf(stdout, "\n");
}