#ifndef _COMMANDS_H_
#define _COMMANDS_H_ 

#include "arch/arch.h"

#define CMD_EXIT_SUCCESS 1
#define CMD_EXIT_FAILURE 0
#define CMD_QUIT 11

#define CMD_EXIT_MISSING_ARG -1
#define CMD_EXIT_INVALID_ADDR -2
#define CMD_EXIT_INVALID_ADDR_VALUE -21
#define CMD_EXIT_INVALID_REG -3
#define CMD_EXIT_INVALID_REG_VALUE -31

#define CMD_NOT_FOUND -4

#define UNUSED(x) (void)(x)

typedef int (*cmd_ptr)(ARCH, char*);

int execute_cmd_da(ARCH, char*);
int execute_cmd_di(ARCH, char*);
int execute_cmd_dm(ARCH, char*);
int execute_cmd_dr(ARCH, char *);
int execute_cmd_ex(ARCH, char*);
int execute_cmd_lm(ARCH, char*);
int execute_cmd_lp(ARCH, char*);
int execute_cmd_lr(ARCH, char*);
int execute_cmd_testcmd(ARCH, char*);
int execute_cmd_help(ARCH, char*);

struct command {
	const char* command;
	cmd_ptr ptr;
	const char* usage;
	const char* help;
};

static struct command cmd_table[] = {
	{"da", execute_cmd_da, "da <address>:<instructions number>", "display assembler"},
	{"dm", execute_cmd_dm, "dm <address>", "display memory"},
	{"dr", execute_cmd_dr, "dr <register>", "display register"},
	{"lm", execute_cmd_lm, "lm <address> <value>", "load memory"},
	{"lp", execute_cmd_lp, "lp <filename>", "load program"},
	{"lr", execute_cmd_lr, "lr <register> <value>", "load register"},
	{"ex", execute_cmd_ex, "", "Quit"},
	{"di", execute_cmd_di, "", "display loaded instructions"},
	{"testcmd", execute_cmd_testcmd, "testcmd <address>", "useful only for testing purpose"},
	{"help", execute_cmd_help, "help [command]", "display command help"},
	{.command = NULL},
};

struct command* find_cmd(char*);

void print_help(struct command*);
void print_help_all(void);
void print_usage(struct command*);
#endif
