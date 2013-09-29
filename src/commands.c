#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch.h"
#include "utils.h"
#include "commands.h"
#include "parsers.h"

/*
	strtok
	char *strtok(char *str, const char *delim);
	return ptr to next token or NULL 

*/


int execute_cmd_ex(ARCH arch)
{
	return quit(arch);
}

int execute_cmd_testcmd(char* str_arg)
{
	int addr;
	char* arg;

	arg = strtok(str_arg, " ");

	/* missing argument */
	if (arg == NULL) {
		print_error("Missing argument");
		return 0;
	}

	/* address not in hexa, or negative */
	if (sscanf(arg, "%x", &addr) != 1 || addr < 0) {
		print_error("Invalid address");
		return 0;
	}

	addr++;

	printf("CMD TEST RESULT 0x%x\n", addr);
	return 1;
}

int execute_cmd_lm(ARCH arch, char* str_arg) 
{
	unsigned int val;
	/*unsigned int addr;*/

	char* args[2];

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		print_error("Missing argument");
		return 0;
	}

	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("error parsing memory address");
		return 0;
	}

	printf("%d\n", parse_addr(arch, args[0]));

	/* 256 = 2^8 = 0xff*/
	/*if ( addr > 0x0fffffff || val > 0xff)
		return 0;*/

	/*(arch->memory)[addr] = val;*/

	return 1;
}

int execute_cmd_lr(ARCH arch, char* str_arg) 
{
	int reg;
	unsigned int val;

	char* args[2];

	args[0] = strtok(str_arg, " ");
	args[1] = strtok(NULL, " ");

	if (args[0] == NULL || args[1] == NULL) {
		print_error("Missing argument");
		return 0;
	}


	if (sscanf(args[1], "%x", &val) != 1) {
		print_error("Invalid value");
		return 0;
	}

	reg = parse_register(args[0]);

	if (reg < 0 || reg > 31) {
		print_error("register does not exist");
		return 0;
	}

	(arch->regs)[reg] = (uint) val;

	return 1;

}