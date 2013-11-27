#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdint.h>
#include "arch/arch.h"
#include "instructions/instructions.h"

int get_breakpoint_id(ARCH, uint);
void add_breakpoint(ARCH, uint);
void del_breakpoint_by_id(ARCH, int);
void del_breakpoint_by_addr(ARCH, uint);
void reset_breakpoints(ARCH);
void display_breakpoints(ARCH);

uint get_register(ARCH, int);
void set_register(ARCH, int, uint);
void reset_register(ARCH, int);
void reset_registers(ARCH);
void set_register_bit(ARCH, int, int);
int get_register_bit(ARCH, int, int);

uint get_section_end(ARCH, int);

uint get_word_from_addr(ARCH, uint);
void set_word_from_addr(ARCH, uint, uint);
uint get_word(unsigned char*);
void set_word(unsigned char*, uint);

void print_decoded_instruction(ARCH, uint);
void print_instruction_bytes(INSTR);
INSTR get_instr_from_addr(ARCH, uint);

int get_desc_id(char*);

void display_reloc_symbol(ARCH, uint);


#endif
