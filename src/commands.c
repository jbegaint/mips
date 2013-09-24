#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"


/*
	strtok
	char *strtok(char *str, const char *delim);

*/

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

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	unsigned int addr, val;

	char* args[2];

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL)
		return 0;

	if (sscanf(args[0], "%x", &addr) != 1 || sscanf(args[1], "%x", &val) != 1) {
		return 0;
	}

	/* premier condition inutile dans le cas ou les 4go 
		sont alloues (tiendra pas dans un int de 4octect) */

	/* 256 = 2^8 = 0xff*/
	if ( addr > 0x0fffffff || val > 0xff)
		return 0;

	(arch->memory)[addr] = val;

	return 1;
}

int execute_cmd_lr(ARCH arch, char* str_arg) 
{
	int reg;
	unsigned int val;
	char* args[2];

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL)
		return 0;

	if (sscanf(args[0], "%d", &reg) != 1 || sscanf(args[1], "%x", &val) != 1)
		return 0;

	if (reg < 0 || reg > 31)
		return 0;

	/*(arch->regs)[reg] = (mem) val;*/
	/*print_info("not implemented yet");*/

	return 1;

}