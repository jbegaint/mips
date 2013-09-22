#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch.h"
#include "commands.h"
#include "utils.h"

/*
	strtok
	char *strtok(char *str, const char *delim);

*/

int execute_cmd(ARCH arch, char* line)
{
	char delim[1] = " ";
	char* cmd = malloc(sizeof(*line));

	strcpy(cmd, line);
	cmd = strtok(cmd, delim);
	
	if (strcmp(cmd, "ex") == 0) {
		return execute_cmd_ex(arch);
	} 
	else if (strcmp(cmd, "testcmd") == 0) {
		return execute_cmd_testcmd(line);
	}
	else if (strcmp(cmd, "lm") == 0) {
		return execute_cmd_lm(arch, line);
	}
	else {
		return 0;
	}
}

int parse_line(ARCH arch, FILE* f)
{
	char buffer[256];
	char* line = NULL;
	line = malloc(sizeof(*line));

	if (fgets(buffer, sizeof(buffer), f) != 0) {
		
		if (sscanf(buffer, "%[^\n]s", line) == 0 || strlen(line) == 0) {
			/* empty line */
			return 1;
		}

		if (line[0] == '#' || line[0] == ' ' ) {
			/* comment line */
			return 1;
		}

		return execute_cmd(arch, line);
	}
	return 2;
}

FILE* open_file(char* filename)
{
	FILE* f = NULL;
	char* error = NULL;

	f = fopen(filename, "r");
	error = malloc(sizeof(*error));

	if (f == NULL) {
		print_error(error);
		exit(EXIT_FAILURE);
	}

	return f;
}

void parse_file(ARCH arch, char* filename)
{
	int res;
	FILE* f;
	f = open_file(filename);

	while (1) {
		res = parse_line(arch, f);

		if (res == 0) {
			/* command return error code */
			die(arch);
		} 
		else if (res == 2) {
			/* end parsing */
			break;
		}

	}

	fclose(f);
}

int main(int argc, char* argv[])
{
	ARCH arch = NULL;
	arch = init_simu(arch, 256);

	if (arch == NULL) {
		die(arch);
	}

	switch(argc) {
		case 1:
			printf("Mode interactif\n");
		
			while (1) {
				printf("-> ");
				if (parse_line(arch, stdin) != 1) {
					break;
				}
			}
			break;

		case 2:
			parse_file(arch, argv[1]);
			break;

		default:
			usage(argv[0]);
			exit(EXIT_FAILURE);
			break;
	}

	free_arch(arch);
	exit(EXIT_SUCCESS);
}
