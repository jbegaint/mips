#ifndef _ARCH_H_
#define _ARCH_H_

#include <stdint.h>
#include "list.h"
#include "elf/elfimport.h"

#define TEXT 0
#define DATA 1
#define BSS 2
#define STACK 3

/* common purpose registers index */
#define SP 29
#define HI 32
#define LO 33 
#define SR 34
#define PC 35

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
	NOT_LOADED,
	PAUSED,
	FINISHED
} state_t;

typedef struct
{
	uint registers[36];
	section_t sections[4];
	state_t state;
	list_t breakpoints;

	Elf32_Sym* symbols;
	Elf32_Word symbols_num;
	char* symbols_names; 
} *ARCH;

typedef union
{
	uint word;
	uchar bytes[4];
} INSTR;

typedef INSTR word_t;

ARCH init_simu(void);
void init_stack(ARCH);
void free_arch(ARCH);

#endif