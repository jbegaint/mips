#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include <stdint.h>

#include "arch/arch.h"

int display_instruction(uint32_t);
int execute_instruction(ARCH, uint32_t);

#endif