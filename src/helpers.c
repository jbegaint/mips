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