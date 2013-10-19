#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "arch.h"
#include "commands.h"
#include "globals.h"
#include "notify.h"
#include "utils.h"

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
	else if (strcmp(cmd, "dm") == 0) {
		return execute_cmd_dm(arch, args);
	}
	else if (strcmp(cmd, "dr") == 0) {
		return execute_cmd_dr(arch, args);
	}
	else if (strcmp(cmd, "lp") == 0) {
		return execute_cmd_lp(arch, args);
	}
	else if (strcmp(cmd, "da") == 0) {
		return execute_cmd_da(arch, args);
	}
	else {
		return CMD_NOT_FOUND;
	}
}

int parse_line(ARCH arch, FILE* f)
{
	char buffer[256];
	char cmd[256];

	memset(buffer, '\0', 256);
	memset(cmd, '\0', 256);

	if (f == stdin) {

		/* interactive mode */
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
		/* script mode */
		if (fgets(buffer, sizeof(buffer), f) != 0) {

			/* empty line */
			if (sscanf(buffer, "%s", cmd) == 0 || strlen(cmd) == 0)
				return PARSING_FILE_NON_CMD_LINE;

			/* comment line */
			if (*cmd == '#')
				return PARSING_FILE_NON_CMD_LINE;

			/* +1 for space character */
			return execute_cmd(arch, cmd, buffer + strlen(cmd) + 1);
		}
		return PARSING_FILE_EXIT_EOF;
	}
}

void switch_return_code(ARCH arch, FILE* f, int* res)
{
	switch (parse_line(arch, f)) {
		case CMD_EXIT_SUCCESS:
			break;

		case CMD_EXIT_MISSING_ARG:
			*res = -1;
			print_error("missing argument(s)");
			break;

		case CMD_EXIT_INVALID_ADDR:
			*res = -1;
			print_error("invalid address");				
			break;

		case CMD_EXIT_INVALID_ADDR_VALUE:
			*res = -1;
			print_error("invalid address value");				
			break;

		case CMD_EXIT_INVALID_REG:
			*res = -1;
			print_error("invalid register");
			break;

		case CMD_EXIT_INVALID_REG_VALUE:
			*res = -1;
			print_error("invalid register value");
			break;

		case CMD_NOT_FOUND:
			*res = -1;
			print_error("I'm sorry Dave, I'm afraid I can't do that.");
			break;

		case CMD_EXIT_FAILURE:
			*res = 0;
			break;

		case CMD_QUIT:
			*res = CMD_QUIT;
			break;

		case PARSING_FILE_NON_CMD_LINE:
			DEBUG_MSG("empty or commented line");
			break;

		case PARSING_FILE_EXIT_EOF:
			*res = PARSING_FILE_EXIT_EOF;
			DEBUG_MSG("end of file");
			break;

		default:
			*res = 0;
			print_error("unknown error code");
			break;
	}
}

void parse_file(ARCH arch, char* filename)
{
	int res = 1;
	FILE* f = NULL;

	f = open_file(filename);

	if (f == NULL)
		die(arch);

	while (res == CMD_EXIT_SUCCESS || res == CMD_QUIT) {
	    switch_return_code(arch, f, &res);
	    if (res == CMD_QUIT) {
	    	break;
	    }
	}

	close_file(f);
	 
	if (res <= 0) {
		/* error code */
	   	die(arch);
	}
}

void parse_interpreter(ARCH arch)
{
	int res = 1;

	while (res != CMD_EXIT_FAILURE && res != CMD_QUIT) {
		switch_return_code(arch, stdin, &res);
	}
}

int main(int argc, char* argv[])
{
	ARCH arch = NULL;
	arch = init_simu(arch);

	print_info("Init");

	if (arch == NULL) {
		print_error("allocation error");
		die(arch);
	}

	switch(argc) {
		case 1:
			print_info("Interactive mode");
			parse_interpreter(arch);
			break;

		case 2:
			print_info("Script mode");
			parse_file(arch, argv[1]);
			break;

		default:
			usage(argv[0]);
			exit(EXIT_FAILURE);
			break;
	}

	print_info("Exit");
	free_arch(arch);
	exit(EXIT_SUCCESS);
}