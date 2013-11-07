#include <stdlib.h>
#include <stdio.h>

#include "arch/arch.h"
#include "desc/desc.h"

#include "instructions/instructions.h"
#include "instructions/parser_instru.h"
#include "instructions/get_instr.h"

#include "notify.h"

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;

int execute_all_instr (uint word, ARCH arch)
{
   /* execute_instr executor[DESC_ARRAY_LENGTH];
    int c;
    int i = 0 ;

    executor[_srl]=execute_srl(uint word, ARCH arch);
    executor[_slt]=execute_slt(uint word, ARCH arch);
    executor[_sll]=execute_sll(uint word, ARCH arch);
    executor[_xor]=execute_xor(uint word, ARCH arch);
    executor[_syscall]=execute_syscall(uint word, ARCH arch);
    executor[_sw]=execute_sw(uint word, ARCH arch);
    executor[_sub]=execute_sub(uint word, ARCH arch);
    executor[_or]=execute_or(uint word, ARCH arch);
    executor[_mult]=execute_mult(uint word, ARCH arch);
    executor[_mflo]=execute_mflo(uint word, ARCH arch);
    executor[_mfhi]=execute_mfhi(uint word, ARCH arch);
    executor[_lw]=execute_lw(uint word, ARCH arch);
    executor[_lui]=execute_lui(uint word, ARCH arch);
    executor[_jr]=execute_jr(uint word, ARCH arch);
    executor[_j]=execute_j(uint word, ARCH arch);
    executor[_jal]=execute_jal(uint word, ARCH arch);
    executor[_bne]=execute_bne(uint word, ARCH arch);
    executor[_blez]=execute_blez(uint word, ARCH arch);
    executor[_rrotr]=execute_rotr(uint word, ARCH arch);
    executor[_beq]=execute_beq(uint word, ARCH arch);
    executor[_and]=execute_and(uint word, ARCH arch);
    executor[_addi]=execute_addi(uint word, ARCH arch);
    executor[_bgtz]=execute_bgtz(uint word, ARCH arch);
    executor[_add]=execute_add(uint word, ARCH arch);

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

int display_all_instr (uint word, ARCH arch)
{
  /*  display_instr display[40];
    int c;
    int i=0;

    display[_srl]=display_srl(uint word, ARCH arch);
    display[_slt]=display_slt(uint word, ARCH arch);
    display[_sll]=display_sll(uint word, ARCH arch);
    display[_xor]=display_xor(uint word, ARCH arch);
    display[_syscall]=display_syscall(uint word, ARCH arch);
    display[_sw]=display_sw(uint word, ARCH arch);
    display[_sub]=display_sub(uint word, ARCH arch);
    display[_or]=display_or(uint word, ARCH arch);
    display[_mult]=display_mult(uint word, ARCH arch);
    display[_mflo]=display_mflo(uint word, ARCH arch);
    display[_mfhi]=display_mfhi(uint word, ARCH arch);
    display[_lw]=display_lw(uint word, ARCH arch);
    display[_lui]=display_lui(uint word, ARCH arch);
    display[_jr]=display_jr(uint word, ARCH arch);
    display[_j]=display_j(uint word, ARCH arch);
    display[_jal]=display_jal(uint word, ARCH arch);
    display[_bne]=display_bne(uint word, ARCH arch);
    display[_blez]=display_blez(uint word, ARCH arch);
    display[_rrotr]=display_rotr(uint word, ARCH arch);
    display[_beq]=display_beq(uint word, ARCH arch);
    display[_and]=display_and(uint word, ARCH arch);
    display[_addi]=display_addi(uint word, ARCH arch);
    display[_bgtz]=display_bgtz(uint word, ARCH arch);
    display[_add]=display_add(uint word, ARCH arch);

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
