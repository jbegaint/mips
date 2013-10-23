#ifndef _DESC_H_
#define _DESC_H_

#include "arch/arch.h"

typedef struct {
	char name[8]; /* todo: check max name length in doc */
	char type;
	uint opcode;
	uint function;
} DESC;

void init_desc_array();
void free_desc_array();

#endif
