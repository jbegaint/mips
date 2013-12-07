#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "arch/arch.h"
#include "desc/desc.h"
#include "desc/desc_utils.h"

#include "globals.h"
#include "commands.h"
#include "notify.h"
#include "utils.h"
#include "simMips.h"
#include "parsers.h"

#include "instructions/instructions.h"

struct command cmd_table[] = {
	/* name, cmd_ptr, usage, help, arg(s) min, args(s) max */
	{"bp", execute_cmd_bp, "bp <address>", "set breakpoint", 1, 1},
	{"da", execute_cmd_da, "da <address>:<instructions number>", "display assembler", 2, 3},
	{"db", execute_cmd_db, "", "display break point", 0, 0},
	{"di", execute_cmd_di, "", "display loaded instructions", 0, 0},
	{"dm", execute_cmd_dm, "dm <address>", "display memory", 1, 3},
	{"dr", execute_cmd_dr, "dr <register>", "display register", 0, -1},
	{"ds", execute_cmd_ds, "", "display section infos", 0, 0},
	{"er", execute_cmd_er, "er <address>", "erase breakpoint", 1, 1},
	{"ex", execute_cmd_ex, "", "exit", 0, 0},
	{"help", execute_cmd_help, "help [command]", "display command help", 0, 1},
	{"lm", execute_cmd_lm, "lm <address> <value>", "load memory", 2, 2},
	{"lp", execute_cmd_lp, "lp <filename>", "load program", 1, 1},
	{"lr", execute_cmd_lr, "lr <register> <value>", "load register", 2, 2},
	{"run", execute_cmd_run, "run [address]", "", 0, 1},
	{"s", execute_cmd_s, "", "run step by step (line per line)", 0, 0},
	{"si", execute_cmd_si, "", "step into", 0, 0},
	{"testcmd", execute_cmd_testcmd, "testcmd <address>", "useful only for testing purpose", 1, 1},
	{.command = NULL},
};

struct command* find_cmd(char* cmd)
{
	for (int i = 0; cmd_table[i].command != NULL; i++) {
		if (strcmp(cmd, cmd_table[i].command) == 0)
			return cmd_table+i;
	}
	return NULL;
}

void print_usage(struct command* command)
{
	fprintf(stderr, "Usage: ");
	if (strcmp(command->usage, "") != 0) 
		fprintf(stderr, "%s\n", command->usage);
	else
		fprintf(stderr, "%s\n", command->command);
}

void print_help(struct command* command)
{
	fprintf(stderr, "Name: %s\n", command->command);
	print_usage(command);
	fprintf(stderr, "Help: %s\n", command->help);
}

void print_help_all(void)
{
	int i;
	int n = 5;
	for (i = 0; cmd_table[i].command != NULL; i++) {
		fprintf(stderr, "%-8s", (cmd_table+i)->command);
		if ((i+1)%n == 0)
			printf("\n");
	}
	if ((i)%n != 0)
		printf("\n");
}

int execute_cmd(ARCH arch, char* cmd, char* str_arg)
{
	int res;
	struct command* command;

	char** args = (char**) calloc(MAX_ARGS, sizeof(*args));

	if ((command = find_cmd(cmd)) == NULL)
		return CMD_NOT_FOUND;

	if (!parse_args(command, str_arg, args)) {
		print_usage(command);
		return CMD_EXIT_ERROR;
	}

	res = command->ptr(arch, args);

	free(args);
	
	return res;
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
			*res = CMD_EXIT_ERROR;
			print_error("missing argument(s)");
			break;

		case CMD_EXIT_INVALID_ADDR:
			*res = CMD_EXIT_ERROR;
			print_error("invalid address");				
			break;

		case CMD_EXIT_INVALID_ADDR_VALUE:
			*res = CMD_EXIT_ERROR;
			print_error("invalid address value");				
			break;

		case CMD_EXIT_INVALID_REG:
			*res = CMD_EXIT_ERROR;
			print_error("invalid register");
			break;

		case CMD_EXIT_INVALID_REG_VALUE:
			*res = CMD_EXIT_ERROR;
			print_error("invalid register value");
			break;

		case CMD_NOT_FOUND:
			*res = CMD_EXIT_ERROR;
			print_error("I'm sorry Dave, I'm afraid I can't do that.");
			break;

		case CMD_EXIT_ERROR:
			*res = CMD_EXIT_ERROR;
			break;

		case CMD_EXIT_FILE_NOT_FOUND:
			*res = CMD_EXIT_ERROR;
			print_error("file not found");
			break;

		case CMD_EXIT_FAILURE:
			*res = CMD_EXIT_FAILURE;
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
			*res = CMD_EXIT_FAILURE;
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

	while (res == CMD_EXIT_SUCCESS )
	    switch_return_code(arch, f, &res);

	close_file(f);
	 
	if (res <= 0) /* error code*/
	   	die(arch);
}

void parse_interpreter(ARCH arch)
{
	int res = 1;

	while (res != CMD_EXIT_FAILURE && res != CMD_QUIT)
		switch_return_code(arch, stdin, &res);
}

int main(int argc, char* argv[])
{
	ARCH arch = NULL;

	print_logo();

	print_info("Init");
	arch = init_simu();

	/* let's init the stack section */
	init_stack(arch);

	init_desc_array();

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
