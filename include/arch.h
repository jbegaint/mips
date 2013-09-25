#pragma once

/*typedef unsigned char mem[4];*/

typedef unsigned int mem;

typedef struct
{
	mem regs[32];
	unsigned char* memory;
} *ARCH;

ARCH init_simu(ARCH, int);
void free_arch(ARCH);