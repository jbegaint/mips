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
	return 1;
}

int execute_cmd_testcmd(char* addr)
{
	int i;

	if (addr == NULL) {
		return 0;
	}

	/* address not in hexa, or negative */
	if (sscanf(addr, "%x", &i) != 1 || i < 0) {
		return 0;
	}

	i++;

	printf("CMD TEST RESULT 0x%x\n", i);
	return 1;
}