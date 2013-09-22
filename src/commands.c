#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"

char** get_args(int length, char* line)
{
	int i;
	char** args;
	char delim[1] = " ";

	args = malloc(length*sizeof(*args));
	if (args == NULL) {
		return NULL;
	}

	strtok(line, delim);

	for (i=0; i < length; i++){
		args[i] = malloc(sizeof(**args));
		if (args[i] == NULL)
			return NULL;
		args[i] = strtok(NULL, delim);
	}

	return args;
}

int execute_cmd_ex(ARCH arch)
{
	quit(arch);
	return 1;
}

int execute_cmd_testcmd(char* arg)
{
	int addr;
	char delim[1] = " ";

	arg = strtok(NULL, delim);

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

int execute_cmd_lm(ARCH arch, char* line) {
	int addr;
	unsigned char val;

	char** args = get_args(2, line);

	int i;
	for (i=0; i < 2; i++) {
		/*printf("%s\n", args[i]);*/
	}

	if (args[0] == NULL || args[1] == NULL)
		return 0;
/*
	if (sscanf(args[0], "%x", &addr) != 1 || sscanf(args[1], "%x", &val) != 1) {
		return 0;
	}*/

	addr = strtol(args[0], NULL, 16);
	val = strtol(args[1], NULL, 16);

	(arch->memory)[addr] = val;

	for (i=0; i < 2; i++) {
		free(*(args+i));
	}
	free(args);

	return 1;
}