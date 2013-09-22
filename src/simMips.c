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

/* execute_simu_nom_de_la_commande */
int execute_cmd(ARCH arch, char* line)
{
	char* cmd;
	char delim[1] = " ";
	
	cmd = strtok(line, delim);

	if (strcmp(cmd, "ex") == 0) {
		return execute_cmd_ex(arch);
	} 
	else if (strcmp(cmd, "testcmd") == 0) {
		cmd = strtok(NULL, delim);
		return execute_cmd_testcmd(cmd);
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
	return 0;
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
	FILE* f;
	f = open_file(filename);

	while (parse_line(arch, f) == 1) {}
	fclose(f);
	/*
	while (1) {
		if (parse_line(f) != 1) {
			break;
		}
	}
	*/
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
