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

uint get_section_end(ARCH, int);

uint get_bytes_from_addr(ARCH, uint);
void set_bytes_from_addr(ARCH, uint, uint);


void print_decoded_instruction(ARCH, uint);
void print_instruction_bytes(INSTR);
INSTR get_instr_from_addr(ARCH, uint);

#endif
