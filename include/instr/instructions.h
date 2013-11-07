#ifndef INSTRUCTIONS_H_INCLUDED
#define INSTRUCTIONS_H_INCLUDED

//#include "arch/arch.h"

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

int execute_all_instr (uint word, ARCH arch);

typedef void (*execute_instr) (uint,ARCH);
typedef void (*display_instr) (uint,ARCH);

void display_add(uint word, ARCH arch);
void display_bgtz(uint word, ARCH arch);
void display_addi(uint word, ARCH arch);
void display_and(uint word, ARCH arch);
void display_beq(uint word, ARCH arch);
void display_rotr(uint word, ARCH arch);
void display_blez(uint word, ARCH arch);
void display_bne(uint word, ARCH arch);
void display_div(uint word, ARCH arch);
void display_j(uint word, ARCH arch);
void display_jal(uint word, ARCH arch);
void display_jr(uint word, ARCH arch);
void display_lui(uint word, ARCH arch);
void display_lw(uint word, ARCH arch);
void display_mfhi(uint word, ARCH arch);
void display_mflo(uint word, ARCH arch);
void display_mult(uint word, ARCH arch);
void display_nop(uint word, ARCH arch);
void display_or(uint word, ARCH arch);
void display_sub(uint word, ARCH arch);
void display_sw(uint word, ARCH arch);
void display_syscall(uint word, ARCH arch);
void display_xor(uint word, ARCH arch);
void display_sll(uint word, ARCH arch);
void display_slt(uint word, ARCH arch);
void display_srl(uint word, ARCH arch);

void execute_srl(uint word, ARCH arch);
void execute_slt(uint word, ARCH arch);
void execute_sll(uint word, ARCH arch);
void execute_xor(uint word, ARCH arch);
void execute_syscall(uint word, ARCH arch);
void execute_sw(uint word, ARCH arch);
void execute_sub(uint word, ARCH arch);
void execute_or(uint word, ARCH arch);
void execute_nop(uint word, ARCH arch);
void execute_mult(uint word, ARCH arch);
void execute_mflo(uint word, ARCH arch);
void execute_mfhi(uint word, ARCH arch);
void execute_lw(uint word, ARCH arch);
void execute_lui(uint word, ARCH arch);
void execute_jr(uint word, ARCH arch);
void execute_j(uint word, ARCH arch);
void execute_j(uint word, ARCH arch);
void execute_div(uint word, ARCH arch);
void execute_bne(uint word, ARCH arch);
void execute_blez(uint word, ARCH arch);
void execute_rotr(uint word, ARCH arch);
void execute_beq(uint word, ARCH arch);
void execute_and(uint word, ARCH arch);
void execute_addi(uint word, ARCH arch);
void execute_bgtz(uint word, ARCH arch);
void execute_add(uint word, ARCH arch);

#endif // INSTRUCTIONS_H_INCLUDED
