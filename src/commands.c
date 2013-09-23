#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"


int execute_cmd_ex(ARCH arch)
{
	return quit(arch);
}

int execute_cmd_testcmd(char* arg)
{
	int addr;

	/* missing argument */
	if (arg == NULL) {
		return 0;
	}

	/* address not in hexa, or negative */
	if (sscanf(arg, "%x", &addr) != 1 || addr < 0) {
		return 0;
	}

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return 1;
}

int execute_cmd_lm(ARCH arch, char* arg) {
	int addr;
	unsigned char val;

	char* args[2];

	args[0] = strtok(arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL)
		return 0;

	printf("%s\n", args[0]);
	printf("%s\n", args[1]);
/*
	if (sscanf(args[0], "%x", &addr) != 1 || sscanf(args[1], "%x", &val) != 1) {
		return 0;
	}*/

	addr = strtol(args[0], NULL, 16);
	val = strtol(args[1], NULL, 16);

	(arch->memory)[addr] = val;

	return 1;
}