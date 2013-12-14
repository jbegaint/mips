#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"

#include "instructions/parser_instructions.h"
#include "notify.h"
#include "utils.h"
#include "helpers.h"

void display(uint32_t word, FILE* stream)
{
    UNUSED(word);
    fprintf(stream, "BREAK\n"); 
}

void execute(ARCH arch)
{
    /* signal breakpoint exceptions */
    set_register_bit(arch, SR, 2);
}

