#include <stdlib.h>

#include "arch.h"
#include "utils.h"

ARCH init_simu(ARCH arch)
{
	int i;
	SECTION* section_ptr;


	arch = malloc(sizeof(*arch));
	if (arch == NULL)
		return NULL;

	/* temporary, should be remove next step */

	arch->sections[TEXT].start_addr = 1024;
	arch->sections[BSS].start_addr = 3*1024;
	arch->sections[DATA].start_addr = 5*1024;

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
	for (i=0; i < 2 ; i++) {
		free((arch->sections[i]).data);
	}

	free(arch);
}