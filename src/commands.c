#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"

void execute_cmd_ex(ARCH arch)
{
	quit(arch);
}

void execute_cmd_testcmd(char* addr)
{
	int i;
	i = strtol(addr, NULL, 16);
	i++;
	
	printf("CMD TEST RESULT 0x%x\n", i);
}