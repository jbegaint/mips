#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <time.h>

#include "arch/arch.h"

#include "notify.h"
#include "utils.h"

void usage(char *arg)
{
	printf("Usage: %s [file]\n", arg);
}

FILE* open_file(char *filepath)
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

void print_section_info(ARCH arch)
{
	for (int i = 0; i < 4; i++)
		fprintf(stderr, "%-7s: %08x %d \n", (arch->sections)[i].name, 
			(arch->sections)[i].start_addr, (arch->sections)[i].size);
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

void swap_str(char** str1, char** str2)
{
	char* tmp = *str1;
	*str1 = *str2;
	*str2 = tmp;
}

/* useless but still ... */
void print_logo(void)
{
	char logo[256] = "  \
   _           __  __ ___ ____  ____  \n\
 ___(_)_ __ ___ |  \\/  |_ _|  _ \\/ ___| \n\
/ __| | '_ ` _ \\| |\\/| || || |_) \\___ \\ \n\
\\__ \\ | | | | | | |  | || ||  __/ ___) | \n\
|___/_|_| |_| |_|_|  |_|___|_|   |____/ \n \
" ;

	/* clear shell output */
	fprintf(stderr, "\033[2J");
	fprintf(stderr, "\033[%d;%df", 0, 0);
	fprintf(stderr, "\n");

	/* print logo */
	fprintf(stderr, "%s\n", logo);
}

void print_bits(uint val)
{
	for (int i = 31; i >= 0; i--)
		fprintf(stderr, "%d", (val >> i) & 1);

	fprintf(stderr, "\n");
}

int get_file_lines_count(FILE* f)
{
	int c, l = 0;

	if (!f)
		return -1;

	while ((c = getc(f)) != EOF)
		if (c == '\n')
		    l++;

	return l;
}

void lower_string(char* str)
{
	for (uint i = 0; i < strlen(str); i++) {
		*(str+i) = tolower(*(str+i));
	}
}
