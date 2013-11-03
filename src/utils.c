#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <string.h>

#include "arch/arch.h"

#include "notify.h"
#include "utils.h"

void usage(char *arg)
{
	printf("Usage: %s [file]\n", arg);
}

/**
	Open file from path
	@param filepath
	@return FILE* or NULL if file does not exist
*/

FILE *open_file(char *filepath)
{
	char buffer[256];
	FILE *f = NULL;

	f = fopen(filepath, "r");

	if (f == NULL) {
		sprintf(buffer, "Error opening \"%s\"", filepath);
		print_error(buffer);
		return NULL;
	}

	DEBUG_MSG("Opening %s", filepath);

	return f;
}

void close_file(FILE * f)
{
	fclose(f);
	DEBUG_MSG("file closed");
}

int quit(ARCH arch)
{
	print_info("Exiting...");
	free_arch(arch);
	exit(EXIT_SUCCESS);
}

int die(ARCH arch)
{
	if (arch != NULL)
		free_arch(arch);
	print_error("Exiting...");
	exit(EXIT_FAILURE);
}

void print_str(char *str, char *type, int color)
{

	time_t timer;
	char buffer[25];
	struct tm *tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, 25, "%H:%M:%S", tm_info);
	fprintf(stderr, "\x1b[%dm[ %s | %s: %s ]\n\x1b[0m", color, buffer,
		type, str);
}

void print_info(char *str)
{
	print_str(str, "Info", 34);
}

void print_error(char *str)
{
	print_str(str, "Error", 31);
}

void print_section_info(SECTION section)
{
	if (0) {
		printf("Section start_addr: %d\n", section.start_addr);
		printf("Section size: %d\n", section.size);
	}
}

uint get_hash(char *cmd)
{
	uint res = 0;

	for (uint i = 0; i < strlen(cmd) && i < 2; i++) {
		res = res * 100;
		res = res + (*(cmd + i) - 'a' + 1);
	}
	
	return res;
}

char bin_to_dec(char *n)
{
	char res = 0;

	for (uint i = 0; i < strlen(n); i++) {
		res = res * 2 + (n[i] - (int) '0');
	}

	return res;
}
