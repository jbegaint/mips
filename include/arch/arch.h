#ifndef _ARCH_H_
#define _ARCH_H_

#define TEXT 0
#define BSS 1
#define DATA 2

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct 
{
	char* name;
	uchar* data;
	uint start_addr;
	uint size;
} SECTION;

typedef struct
{
	uint regs[32];
	SECTION sections[3];
} *ARCH;


ARCH init_simu(void);
void free_arch(ARCH);

#endif