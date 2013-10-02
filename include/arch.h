#pragma once

#define TEXT 0
#define BSS 1
#define DATA 2

/*
	section size * by X Mo
*/

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct 
{
	uchar* data;
	uint start_addr;
	uint size;
} SECTION;

typedef struct
{
	uint regs[32];
	SECTION sections[3];
} *ARCH;


void free_arch(ARCH);
ARCH init_simu(ARCH);