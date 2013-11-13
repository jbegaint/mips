#include "arch/arch.h"
#include "arch/section.h"

int get_section(ARCH arch, uint addr)
{
	section_t* section_ptr;

	for (int i = 0; i < 3; i++) {
		section_ptr = &(arch->sections[i]);

		if ( addr >= section_ptr->start_addr 
			&& addr < section_ptr->start_addr + section_ptr->size)
			return i;
	}

	return -1;
}

int get_offset(ARCH arch, uint addr, int section_index) 
{
	return addr - (arch->sections)[section_index].start_addr;
}