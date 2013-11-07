#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <stdint.h>

#include "arch/arch.h"

typedef void (*display_instr)(ARCH, uint32_t);
typedef void (*execute_instr)(ARCH, uint32_t);

void display_addi(ARCH, uint32_t);


#include "arch/arch.h"

enum
{
    _add = 0,
    _bgtz,
    _addi,
    _and,
    _beq,
    _rrotr,
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
    _sub,
    _sw,
    _syscall,
    _xor,
    _slt,
    _sll,
    _srl
};
char *_instr[]=
{
    "add",
    "bgtz",
    "addi",
    "and",
    "beq",
    "rrotr",
    "blez",
    "bne",
    "div",
    "j",
    "jal",
    "jr",
    "lui",
    "lw",
    "mfhi",
    "mflo",
    "mult",
    "or",
    "sub",
    "sw",
    "syscall",
    "xor",
    "slt",
    "sll",
    "srl"
};

int execute_all_instr (ARCH arch, uint32_t word);

void display_add(ARCH arch, uint32_t word);
void execute_add(ARCH arch, uint32_t word);

void display_addi(ARCH arch, uint32_t word);
void execute_addi(ARCH arch, uint32_t word);

void display_and(ARCH arch, uint32_t word);
void execute_and(ARCH arch, uint32_t word);

void display_beq(ARCH arch, uint32_t word);
void execute_beq(ARCH arch, uint32_t word);

void display_bgtz(ARCH arch, uint32_t word);
void display_blez(ARCH arch, uint32_t word);
void display_bne(ARCH arch, uint32_t word);
void display_div(ARCH arch, uint32_t word);
void display_j(ARCH arch, uint32_t word);
void display_jal(ARCH arch, uint32_t word);
void display_jr(ARCH arch, uint32_t word);
void display_lui(ARCH arch, uint32_t word);
void display_lw(ARCH arch, uint32_t word);
void display_mfhi(ARCH arch, uint32_t word);
void display_mflo(ARCH arch, uint32_t word);
void display_mult(ARCH arch, uint32_t word);
void display_nop(ARCH arch, uint32_t word);
void display_or(ARCH arch, uint32_t word);
void display_rotr(ARCH arch, uint32_t word);
void display_sll(ARCH arch, uint32_t word);
void display_slt(ARCH arch, uint32_t word);
void display_srl(ARCH arch, uint32_t word);
void display_sub(ARCH arch, uint32_t word);
void display_sw(ARCH arch, uint32_t word);
void display_syscall(ARCH arch, uint32_t word);
void display_xor(ARCH arch, uint32_t word);
void execute_bgtz(ARCH arch, uint32_t word);
void execute_blez(ARCH arch, uint32_t word);
void execute_bne(ARCH arch, uint32_t word);
void execute_div(ARCH arch, uint32_t word);
void execute_j(ARCH arch, uint32_t word);
void execute_j(ARCH arch, uint32_t word);
void execute_jr(ARCH arch, uint32_t word);
void execute_lui(ARCH arch, uint32_t word);
void execute_lw(ARCH arch, uint32_t word);
void execute_mfhi(ARCH arch, uint32_t word);
void execute_mflo(ARCH arch, uint32_t word);
void execute_mult(ARCH arch, uint32_t word);
void execute_nop(ARCH arch, uint32_t word);
void execute_or(ARCH arch, uint32_t word);
void execute_rotr(ARCH arch, uint32_t word);
void execute_sll(ARCH arch, uint32_t word);
void execute_slt(ARCH arch, uint32_t word);
void execute_srl(ARCH arch, uint32_t word);
void execute_sub(ARCH arch, uint32_t word);
void execute_sw(ARCH arch, uint32_t word);
void execute_syscall(ARCH arch, uint32_t word);
void execute_xor(ARCH arch, uint32_t word);

#endif