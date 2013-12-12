#include <stdlib.h>
#include <string.h>

#include "arch/arch.h"

#include "desc/desc.h"

#include "list.h"
#include "utils.h"
#include "helpers.h"

void init_stack(ARCH arch)
{
	/* allocate stack section */
	arch->sections[STACK].start_addr = arch->sections[BSS].start_addr + 0x1000;
	arch->sections[STACK].size = 0x1000;
	arch->sections[STACK].data = (uchar*) calloc(0x1000, sizeof(uchar));

	arch->sections[STACK].name = (char*) calloc(256, sizeof(char));
	strcpy(arch->sections[STACK].name, ".stack");

	/* set stack address at the end of stack */
	set_register(arch, SP, arch->sections[STACK].start_addr + arch->sections[STACK].size - 4);
}

ARCH init_simu(void)
{
	section_t* section_ptr;
	ARCH arch;

	arch = (ARCH) calloc(1, sizeof(*arch));
	if (arch == NULL)
		return NULL;

	/* temporary alloc, mostly useful for tests */

	arch->sections[TEXT].start_addr = 0x400;
	arch->sections[BSS].start_addr = 0xc00;
	arch->sections[DATA].start_addr = 0x1400;

	for (int i = 0; i < 3 ; i++) {
		section_ptr = &(arch->sections[i]);
		section_ptr->size = 1024;
		section_ptr->data = (uchar*) calloc((section_ptr->size)*1024, sizeof(uchar));

		if (section_ptr->data == NULL)
			return NULL;
	}

	/* let's init the stack section */
	init_stack(arch);

	arch->state = NOT_LOADED;
	arch->breakpoints = init_list();

	return arch;
}

void free_arch(ARCH arch)
{
	/* free text, data, bss sections */
	for (int i = 0; i < 4 ; i++) {
		free((arch->sections[i]).name);
		free((arch->sections[i]).data);
	}

	/* free symbol table */
	free(arch->symbols);

	/* free breakpoints list */
	if (!is_list_empty(arch->breakpoints)) {
		fprintf(stderr, "free breakpoints\n");
		free_list(arch->breakpoints);
	}

	free(arch->symbols_names);

	/* free instructions array*/
	free_desc_array();

	/* last but not least */
	free(arch);
}