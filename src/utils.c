#include <stdlib.h>
#include <stdio.h>

#include "arch.h"
#include "utils.h"

void usage(char* arg)
{
	printf("Usage: %s [file]\n", arg);
}

int quit(ARCH arch) 
{
	free_arch(arch);
	exit(EXIT_SUCCESS);
}

int die(ARCH arch)
{
	if (arch != NULL)
		free_arch(arch);
	exit(EXIT_FAILURE);
}

void print_str(char* str, int color)
{
	printf("\x1b[%dm%s\n\x1b[0m", color, str);
}

void print_info(char* str)
{
	print_str(str, 34);
}

void print_error(char* str)
{
	print_str(str, 31);
}