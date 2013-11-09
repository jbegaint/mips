#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "notify.h"
#include "run.h"

state_t STATE;

void run(ARCH arch)
{
	DEBUG_MSG("run start");

	while (get_pc(arch) < get_section_end(arch, TEXT)) {
		fprintf(stderr, "%08x\n", get_pc(arch));

		set_pc(arch, get_pc(arch) + 4);

		if (get_breakpoint_id(get_pc(arch)) != -1)
			break;
	}

	if (get_pc(arch) == get_section_end(arch, TEXT)) {
		fprintf(stderr, "%s\n", "THIS IS THE END");
	}

	DEBUG_MSG("run stop");
}