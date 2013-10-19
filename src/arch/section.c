#include "arch/arch.h"
#include "arch/section.h"

int get_section(ARCH arch, uint addr)
{
	int i;
	SECTION* section_ptr;

	for (i=0; i < 3; i++) {
		section_ptr = &(arch->sections[i]);

		if ( addr >= section_ptr->start_addr 
			&& addr < section_ptr->start_addr + section_ptr->size) {
			return i;
		}
	}

	return -1;
}

int get_offset(ARCH arch, uint addr, int section_index) 
{
	return addr - (arch->sections)[section_index].start_addr;
}