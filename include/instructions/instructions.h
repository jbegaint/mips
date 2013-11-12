#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <stdint.h>

#include "arch/arch.h"

typedef void (*display_instr)(ARCH, uint32_t);
typedef void (*execute_instr)(ARCH, uint32_t);

void init_display(void);
void free_display(void);

int display_instruction(uint32_t);

int execute_all_instr(ARCH, uint32_t);

void display_add(ARCH, uint32_t);
void execute_add(ARCH, uint32_t);

void display_addi(ARCH, uint32_t);
void execute_addi(ARCH, uint32_t);

void display_and(ARCH, uint32_t);
void execute_and(ARCH, uint32_t);

void display_beq(ARCH, uint32_t);
void execute_beq(ARCH, uint32_t);

void display_bgtz(ARCH, uint32_t);
void display_blez(ARCH, uint32_t);
void display_bne(ARCH, uint32_t);
void display_div(ARCH, uint32_t);
void display_j(ARCH, uint32_t);
void display_jal(ARCH, uint32_t);
void display_jr(ARCH, uint32_t);
void display_lui(ARCH, uint32_t);
void display_lw(ARCH, uint32_t);
void display_mfhi(ARCH, uint32_t);
void display_mflo(ARCH, uint32_t);
void display_mult(ARCH, uint32_t);
void display_nop(ARCH, uint32_t);
void display_or(ARCH, uint32_t);
void display_rotr(ARCH, uint32_t);
void display_sll(ARCH, uint32_t);
void display_slt(ARCH, uint32_t);
void display_srl(ARCH, uint32_t);
void display_sub(ARCH, uint32_t);
void display_sw(ARCH, uint32_t);
void display_syscall(ARCH, uint32_t);
void display_xor(ARCH, uint32_t);

void execute_bgtz(ARCH, uint32_t);
void execute_blez(ARCH, uint32_t);
void execute_bne(ARCH, uint32_t);
void execute_div(ARCH, uint32_t);
void execute_j(ARCH, uint32_t);
void execute_j(ARCH, uint32_t);
void execute_jr(ARCH, uint32_t);
void execute_lui(ARCH, uint32_t);
void execute_lw(ARCH, uint32_t);
void execute_mfhi(ARCH, uint32_t);
void execute_mflo(ARCH, uint32_t);
void execute_mult(ARCH, uint32_t);
void execute_nop(ARCH, uint32_t);
void execute_or(ARCH, uint32_t);
void execute_rotr(ARCH, uint32_t);
void execute_sll(ARCH, uint32_t);
void execute_slt(ARCH, uint32_t);
void execute_srl(ARCH, uint32_t);
void execute_sub(ARCH, uint32_t);
void execute_sw(ARCH, uint32_t);
void execute_syscall(ARCH, uint32_t);
void execute_xor(ARCH, uint32_t);

#endif