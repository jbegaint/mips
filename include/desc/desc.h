#ifndef _DESC_H_
#define _DESC_H_

#include "arch/arch.h"

typedef void (*display_f)(uint);
typedef void (*execute_f)(ARCH, uint);

typedef struct {
	char name[8]; /* todo: check max name length in doc */
	char type;
	uint opcode;
	uint function;
	display_f display;
	execute_f execute;
} DESC;

void init_desc_array();
void free_desc_array();

#endif
