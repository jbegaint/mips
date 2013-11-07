#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <stdint.h>

#include "arch/arch.h"

typedef void (*display_instr)(ARCH, uint32_t);
typedef void (*execute_instr)(ARCH, uint32_t);

void display_addi(ARCH, uint32_t);

#endif