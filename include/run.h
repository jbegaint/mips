#ifndef _RUN_H_
#define _RUN_H_

#include "arch/arch.h"

typedef enum {
	NOT_STARTED,
	PAUSED,
	FINISHED
} state_t;

void run(ARCH);

#endif