#include "arch.h"
#include "address.h"

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