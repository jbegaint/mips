#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

typedef void (*display_instr)(ARCH, uint32_t);

void display_addi(ARCH, uint32_t);

#endif