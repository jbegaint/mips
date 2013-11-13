#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdint.h>
#include "arch/arch.h"

void add_breakpoint(ARCH, uint);
void del_breakpoint_by_id(ARCH, int);
void del_breakpoint_by_addr(ARCH, uint);
int get_breakpoint_id(ARCH, uint);
void reset_breakpoints(ARCH);


void set_register(ARCH arch, int index, uint value);
uint get_register(ARCH arch, int index);

void reset_sr(ARCH);
void set_SR(ARCH, uint);
uint get_sr(ARCH);

uint get_section_end(ARCH, int);

void reset_registers(ARCH);

void print_decoded_instruction(ARCH, uint);

#endif