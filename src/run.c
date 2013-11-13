#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "notify.h"
#include "run.h"

void run(ARCH arch)
{
	DEBUG_MSG("run start");

	if (arch->state == FINISHED)
		reset_registers(arch);

	while (get_register(arch, PC) < get_section_end(arch, TEXT)) {
		fprintf(stderr, "%08x\n", get_register(arch, PC));

		/* reset_sr puis execution */

		set_register(arch, PC, get_register(arch, PC) + 4);

		if (get_breakpoint_id(arch, get_register(arch, PC)) != -1) {
			arch->state = PAUSED;
			DEBUG_MSG("state: PAUSED");
			del_breakpoint_by_addr(arch, get_register(arch, PC));
			break;
		}
	}

	if (get_register(arch, PC) == get_section_end(arch, TEXT)) {
		DEBUG_MSG("state: FINISHED");
		arch->state = FINISHED;
	}

	DEBUG_MSG("run stop");
}