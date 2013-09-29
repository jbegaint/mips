#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "arch.h"
#include "commands.h"
#include "utils.h"
#include "globals.h"

int execute_cmd(ARCH arch, char* cmd, char* args)
{

	if (strcmp(cmd, "ex") == 0) {
		return execute_cmd_ex(arch);
	} 
	else if (strcmp(cmd, "testcmd") == 0) {
		return execute_cmd_testcmd(args);
	}
	else if (strcmp(cmd, "lm") == 0) {
		return execute_cmd_lm(arch, args);
	}
	else if (strcmp(cmd, "lr") == 0) {
		return execute_cmd_lr(arch, args);
	}
	else {
		print_error("I'm sorry Dave I'm afraid I can't do that");
		return 0;
	}
}

int parse_line(ARCH arch, FILE* f)
{
	char buffer[256];
	char* cmd = malloc(sizeof(*cmd));

	memset(buffer, '\0', 256);

	if (f == stdin) {
		char *line = readline("-> ");

		if (strlen(line) == 0) {
			print_error("empty command");
       		return 1;
    	}

    	if (sscanf(line, "%s", cmd) != 1) {
			print_error("error parsing command");
			return 1;
		}

        add_history(line);
        strcpy(buffer, line);
        free(line);

       	return execute_cmd(arch, cmd, buffer + strlen(cmd) + 1);
	}
	else {

		if (fgets(buffer, sizeof(buffer), f) != 0) {

			/* empty line */
			if (sscanf(buffer, "%s", cmd) == 0 || strlen(cmd) == 0) {
				return 1;
			}

			/* comment line */
			if (cmd[0] == '#') {
				return 1;
			}

			/* +1 for space */
			return execute_cmd(arch, cmd, buffer + strlen(cmd) + 1);
		}
		return 2;
	}
}

FILE* open_file(char* filename)
{
	char buffer[256];
	FILE* f = NULL;

	f = fopen(filename, "r");

	if (f == NULL) {
		sprintf(buffer, "Erreur lors de l'ouverture de %s", filename);
		print_error(buffer);
		exit(EXIT_FAILURE);
	}

	sprintf(buffer, "Opening %s", filename);
	print_info(buffer);

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
			fclose(f);
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
	arch = init_simu(arch);

	if (arch == NULL) {
		print_error("Erreur d'allocation");
		die(arch);
	}

	switch(argc) {
		case 1:
			print_info("Interactive mode");
		
			while (1) {
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

	print_info("Exiting...");
	free_arch(arch);
	exit(EXIT_SUCCESS);
}
