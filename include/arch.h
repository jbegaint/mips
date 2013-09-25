#pragma once

typedef unsigned int uint;

typedef struct
{
	uint regs[32];
	SECTION sections[3];
} *ARCH;

typedef struct 
{
	unsigned char* data;
	uint start_addr;
	uint size;
} SECTION;

void free_arch(ARCH);
ARCH init_simu(ARCH, int);