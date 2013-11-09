#include <stdlib.h>
#include <stdint.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "list.h"

list_t BP_LIST;

/* BREAKPOINTS */
void set_breakpoint(uint32_t address)
{
	if (get_breakpoint_id(address) == -1)
		BP_LIST = (list_t) add_sort(&address, BP_LIST, sizeof(uint32_t));
}

void del_breakpoint(int id)
{
	BP_LIST = (list_t) del_elt_n(BP_LIST, id);
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
	arch->regs[PC] = address;
}

uint32_t get_pc(ARCH arch)
{
	return arch->regs[PC];
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
		arch->regs[i] = 0;
}
