#pragma once

#include "arch.h"

/*#define CMD_EXIT_OK 1*/
/*#define CMD_MISSING_ARG -1*/

int execute_cmd_ex(ARCH);
int execute_cmd_testcmd(char*);
int execute_cmd_lm(ARCH, char*);
int execute_cmd_lr(ARCH, char*);