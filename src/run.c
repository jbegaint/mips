#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "helpers.h"
#include "notify.h"
#include "run.h"


void run(ARCH arch, int flag)
{
	DEBUG_MSG("run start");
	INSTR instr;
	int syscall_bit = 0;

	if (arch->state == FINISHED)
		reset_registers(arch);

	while (get_register(arch, PC) < get_section_end(arch, TEXT)) {
		
		/* reset_sr then execution */
		reset_register(arch, SR);
		
		instr = get_instr_from_addr(arch, get_register(arch, PC));

		set_register(arch, PC, get_register(arch, PC) + 4);
		
		execute_instruction(arch, instr.word);
		display_instruction(instr.word, stdout);

		if (get_breakpoint_id(arch, get_register(arch, PC)) != -1) {
			arch->state = PAUSED;
			DEBUG_MSG("state: PAUSED");
			del_breakpoint_by_addr(arch, get_register(arch, PC));
			break;
		}

		/* if run with si */
		if (flag)
			break;

		/* check if syscall was called */
		if ((syscall_bit = get_register_bit(arch, SR, 1))) 
			break;
	}

	if (get_register(arch, PC) == get_section_end(arch, TEXT)) {
		DEBUG_MSG("state: FINISHED");
		arch->state = FINISHED;
	}

	DEBUG_MSG("run stop");
}