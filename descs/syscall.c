#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "helpers.h"
#include "notify.h"
#include "utils.h"

void display(uint32_t word, FILE* stream)
{
	UNUSED(word);
    fprintf(stream, "SYSCALL\n");
}

void execute(ARCH arch)
{
	/* unused bit in sr, let's use it */
	set_register_bit(arch, SR, 1);
}
