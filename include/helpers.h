#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdint.h>
#include "arch/arch.h"

void set_breakpoint(uint32_t);
void del_breakpoint_by_id(int);
void del_breakpoint_by_addr(uint32_t);
int get_breakpoint_id(uint32_t);
void reset_breakpoints(void);


void set_register(ARCH arch, int index, uint32_t value);
uint32_t get_register(ARCH arch, int index);

void reset_sr(ARCH);
void set_SR(ARCH, uint32_t);
uint32_t get_sr(ARCH);

uint32_t get_section_end(ARCH, int);

void reset_registers(ARCH);

void print_decoded_instruction(ARCH, uint32_t);

#endif