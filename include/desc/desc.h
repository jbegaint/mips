#ifndef _DESC_H_
#define _DESC_H_

#include "arch/arch.h"

typedef void (*display_f)();
typedef void (*execute_f)();

typedef struct {
	char name[8];
	char type;
	uint opcode;
	uint function;
	display_f display;
	execute_f execute;
	void* plugin;
} DESC;

void init_desc_array();
void free_desc_array();

#endif
