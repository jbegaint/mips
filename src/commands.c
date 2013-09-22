#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"

int execute_cmd_ex(ARCH arch)
{
	quit(arch);
	return 0;
}

int execute_cmd_testcmd(char* addr)
{
	unsigned int i;

	if (addr == NULL) {
		return 0;
	}

	if (sscanf(addr, "%x", &i) != 1) {
		return 0;
	}
		
	printf("CMD TEST RESULT 0x%x\n", i++);
	return 1;
}