#include <stdlib.h>

#include "arch/arch.h"

#include "utils.h"

ARCH init_simu(void)
{
	int i;
	SECTION* section_ptr;

	ARCH arch = malloc(sizeof(*arch));
	if (arch == NULL)
		return NULL;

	/* temporary, should be remove next step */

	arch->sections[TEXT].start_addr = 0x400;
	arch->sections[BSS].start_addr = 0xc00;
	arch->sections[DATA].start_addr = 0x1400;

	for (i=0; i < 3 ; i++) {
		section_ptr = &(arch->sections[i]);
		section_ptr->size = 1024;
		section_ptr->data = malloc((section_ptr->size)*1024);

		if (section_ptr->data == NULL)
			return NULL;
	}

	for (i=0; i<3; i++) {
		print_section_info(arch->sections[i]);
	}

	return arch;
}

void free_arch(ARCH arch)
{
	int i;
	/* free text, data, bss sections */
	for (i=0; i < 3 ; i++) {
		free((arch->sections[i]).data);
	}

	free(arch);
}