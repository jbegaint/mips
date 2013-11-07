#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "desc/desc.h"

#include "instructions/instructions.h"
#include "instructions/parser_instructions.h"
#include "instructions/get_instructions.h"

#include "notify.h"

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;

int execute_all_instr (ARCH arch, uint32_t word)
{
   /* execute_instr executor[DESC_ARRAY_LENGTH];
    int c;
    int i = 0 ;

    executor[_srl]=execute_srl(ARCH arch, uint32_t word);
    executor[_slt]=execute_slt(ARCH arch, uint32_t word);
    executor[_sll]=execute_sll(ARCH arch, uint32_t word);
    executor[_xor]=execute_xor(ARCH arch, uint32_t word);
    executor[_syscall]=execute_syscall(ARCH arch, uint32_t word);
    executor[_sw]=execute_sw(ARCH arch, uint32_t word);
    executor[_sub]=execute_sub(ARCH arch, uint32_t word);
    executor[_or]=execute_or(ARCH arch, uint32_t word);
    executor[_mult]=execute_mult(ARCH arch, uint32_t word);
    executor[_mflo]=execute_mflo(ARCH arch, uint32_t word);
    executor[_mfhi]=execute_mfhi(ARCH arch, uint32_t word);
    executor[_lw]=execute_lw(ARCH arch, uint32_t word);
    executor[_lui]=execute_lui(ARCH arch, uint32_t word);
    executor[_jr]=execute_jr(ARCH arch, uint32_t word);
    executor[_j]=execute_j(ARCH arch, uint32_t word);
    executor[_jal]=execute_jal(ARCH arch, uint32_t word);
    executor[_bne]=execute_bne(ARCH arch, uint32_t word);
    executor[_blez]=execute_blez(ARCH arch, uint32_t word);
    executor[_rrotr]=execute_rotr(ARCH arch, uint32_t word);
    executor[_beq]=execute_beq(ARCH arch, uint32_t word);
    executor[_and]=execute_and(ARCH arch, uint32_t word);
    executor[_addi]=execute_addi(ARCH arch, uint32_t word);
    executor[_bgtz]=execute_bgtz(ARCH arch, uint32_t word);
    executor[_add]=execute_add(ARCH arch, uint32_t word);

    c=get_instr(word);
    if c==NO_MATCH
    {
        return NO_MATCH
    }
    for (i=0;i<DESC_ARRAY_LENGTH;i++)
    {
        if ( strcmp(_instr[i],DESC_ARRAY[c].name)
        {
            break;
        }
    }
    if (i==DESC_ARRAY_LENGTH)
    {
        return NO_MATCH;
    }
    executor[i](word,arch);
    */

    return 1;
}

int display_all_instr (ARCH arch, uint32_t word)
{
  /*  display_instr display[40];
    int c;
    int i=0;

    display[_srl]=display_srl(ARCH arch, uint32_t word);
    display[_slt]=display_slt(ARCH arch, uint32_t word);
    display[_sll]=display_sll(ARCH arch, uint32_t word);
    display[_xor]=display_xor(ARCH arch, uint32_t word);
    display[_syscall]=display_syscall(ARCH arch, uint32_t word);
    display[_sw]=display_sw(ARCH arch, uint32_t word);
    display[_sub]=display_sub(ARCH arch, uint32_t word);
    display[_or]=display_or(ARCH arch, uint32_t word);
    display[_mult]=display_mult(ARCH arch, uint32_t word);
    display[_mflo]=display_mflo(ARCH arch, uint32_t word);
    display[_mfhi]=display_mfhi(ARCH arch, uint32_t word);
    display[_lw]=display_lw(ARCH arch, uint32_t word);
    display[_lui]=display_lui(ARCH arch, uint32_t word);
    display[_jr]=display_jr(ARCH arch, uint32_t word);
    display[_j]=display_j(ARCH arch, uint32_t word);
    display[_jal]=display_jal(ARCH arch, uint32_t word);
    display[_bne]=display_bne(ARCH arch, uint32_t word);
    display[_blez]=display_blez(ARCH arch, uint32_t word);
    display[_rrotr]=display_rotr(ARCH arch, uint32_t word);
    display[_beq]=display_beq(ARCH arch, uint32_t word);
    display[_and]=display_and(ARCH arch, uint32_t word);
    display[_addi]=display_addi(ARCH arch, uint32_t word);
    display[_bgtz]=display_bgtz(ARCH arch, uint32_t word);
    display[_add]=display_add(ARCH arch, uint32_t word);

    c=get_instr(word);
    if c==NO_MATCH
    {
        return NO_MATCH
    }

    for (i=0;i<DESC_ARRAY_LENGTH;i++)
    {
        if ( strcmp(_instr[i],DESC_ARRAY[c].name)
        {
            break;
        }
    }
    if (i==DESC_ARRAY_LENGTH)
    {
        return NO_MATCH;
    }
    display[i](word,arch);
*/
    return 1;
}
