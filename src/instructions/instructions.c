#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

#include "arch/arch.h"
#include "desc/desc.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

display_instr *display;
execute_instr *executor;

enum
{
    _add,
    _addi,
    _and,
    _beq,
    _bgtz,
    _blez,
    _bne,
    _div,
    _j,
    _jal,
    _jr,
    _lui,
    _lw,
    _mfhi,
    _mflo,
    _mult,
    _or,
    _rrotr,
    _sll,
    _slt,
    _srl,
    _sub,
    _sw,
    _syscall,
    _xor
};

void init_display()
{
    display = malloc(DESC_ARRAY_LENGTH*sizeof(*display));

    display[_add] = display_add;
    display[_addi] = display_addi;
    display[_and] = display_and;
    display[_beq] = display_beq;
    display[_bgtz] = display_bgtz;
    display[_blez] = display_blez;
    display[_bne] = display_bne;
    display[_j] = display_j;
    display[_jal] = display_jal;
    display[_jr] = display_jr;
    display[_lui] = display_lui;
    display[_lw] = display_lw;
    display[_mfhi] = display_mfhi;
    display[_mflo] = display_mflo;
    display[_mult] = display_mult;
    display[_or] = display_or;
    display[_rrotr] = display_rotr;
    display[_sll] = display_sll;
    display[_slt] = display_slt;
    display[_srl] = display_srl;
    display[_sub] = display_sub;
    display[_sw] = display_sw;
    display[_syscall] = display_syscall;
    display[_xor] = display_xor;
}

void free_display()
{
    free(display);
}

int display_instruction(uint32_t word)
{
    int c;

    if ((c = get_instr(word)) == NO_MATCH)
        return NO_MATCH;

    display[c](NULL, word);

    return MATCH;
}

int display_all_instr (ARCH arch, uint32_t word)
{/*
    int c;
    int i = 0;*/
/*    if ((c = get_instr(word)) == NO_MATCH)
        return NO_MATCH;
    }

    for (i = 0; i < DESC_ARRAY_LENGTH; i++) {
        if (strcmp(_instr[i], DESC_ARRAY[c].name)
            break;
    }

    if (i == DESC_ARRAY_LENGTH)
        return NO_MATCH;

    display[i](word, arch);*/

    return 1;
}

int init_executor(ARCH arch, uint32_t word)
{
    /*

    int c;
    int i = 0;*/

   /* executor[_add] = execute_add(ARCH arch, uint32_t word);
    executor[_addi] = execute_addi(ARCH arch, uint32_t word);
    executor[_and] = execute_and(ARCH arch, uint32_t word);
    executor[_beq] = execute_beq(ARCH arch, uint32_t word);
    executor[_bgtz] = execute_bgtz(ARCH arch, uint32_t word);
    executor[_blez] = execute_blez(ARCH arch, uint32_t word);
    executor[_bne] = execute_bne(ARCH arch, uint32_t word);
    executor[_j] = execute_j(ARCH arch, uint32_t word);
    executor[_jal] = execute_jal(ARCH arch, uint32_t word);
    executor[_jr] = execute_jr(ARCH arch, uint32_t word);
    executor[_lui] = execute_lui(ARCH arch, uint32_t word);
    executor[_lw] = execute_lw(ARCH arch, uint32_t word);
    executor[_mfhi] = execute_mfhi(ARCH arch, uint32_t word);
    executor[_mflo] = execute_mflo(ARCH arch, uint32_t word);
    executor[_mult] = execute_mult(ARCH arch, uint32_t word);
    executor[_or] = execute_or(ARCH arch, uint32_t word);
    executor[_rrotr] = execute_rotr(ARCH arch, uint32_t word);
    executor[_sll] = execute_sll(ARCH arch, uint32_t word);
    executor[_slt] = execute_slt(ARCH arch, uint32_t word);
    executor[_srl] = execute_srl(ARCH arch, uint32_t word);
    executor[_sub] = execute_sub(ARCH arch, uint32_t word);
    executor[_sw] = execute_sw(ARCH arch, uint32_t word);
    executor[_syscall] = execute_syscall(ARCH arch, uint32_t word);
    executor[_xor] = execute_xor(ARCH arch, uint32_t word);
*/

   /* if ((c = get_instr(word)) == NO_MATCH)
        return NO_MATCH;
    }

    for (i = 0; i < DESC_ARRAY_LENGTH; i++) {
        if (strcmp(_instr[i], DESC_ARRAY[c].name)
            break;
    }

    if (i == DESC_ARRAY_LENGTH)
        return NO_MATCH;

    executor[i](word, arch);
*/
    return 1;
}