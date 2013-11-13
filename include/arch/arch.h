#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>

#define TEXT 0
#define DATA 1
#define BSS 2

typedef uint32_t uint;
typedef unsigned char uchar;

typedef struct 
{
	char* name;
	uchar* data;
	uint start_addr;
	uint size;
} section_t;

typedef enum {
	NOT_STARTED,
	STEP,
	PAUSED,
	FINISHED
} state_t;

typedef struct
{
	uint registers[36];
	section_t sections[3];
	state_t state;
} *ARCH;

typedef union
{
	uint word;
	uchar bytes[4];
} INSTR;


ARCH init_simu(void);
void free_arch(ARCH);

#endif