#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "desc/desc.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

int display_instruction(uint word)
{
    int c;

    if ((c = get_instr(word)) == NO_MATCH)
        return NO_MATCH;

    DESC_ARRAY[c].display(word);

    return MATCH;
}

int execute_instruction(ARCH arch, uint word)
{
    int c;
    
    if ((c = get_instr(word)) == NO_MATCH)
        return NO_MATCH;

    DEBUG_MSG("execute: %s", DESC_ARRAY[c].name);
    DESC_ARRAY[c].execute(arch, word);

    return MATCH;
}