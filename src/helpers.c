#include <stdlib.h>
#include <stdint.h>

#include "helpers.h"
#include "list.h"
#include "arch/arch.h"

#include "globals.h"

list_t BP_LIST;

void set_breakpoint(uint32_t address)
{
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