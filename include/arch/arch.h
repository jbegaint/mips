#ifndef _ARCH_H_
#define _ARCH_H_

#define TEXT 0
#define DATA 1
#define BSS 2

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
	uint regs[36];
	SECTION sections[3];
} *ARCH;

typedef union
{
	uint word;
	uchar bytes[4];
} INSTR;


ARCH init_simu(void);
void free_arch(ARCH);

#endif