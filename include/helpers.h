#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdint.h>
#include "arch/arch.h"

void set_breakpoint(uint32_t);
void del_breakpoint(int);
int get_breakpoint_id(uint32_t);
void reset_breakpoints(void);

void set_pc(ARCH, uint32_t);
uint32_t get_pc(ARCH);

uint32_t get_section_end(ARCH, int);

void reset_registers(ARCH);

#endif