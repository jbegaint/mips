#pragma once

#include "arch.h"

#define CMD_EXIT_SUCCESS 1
#define CMD_EXIT_FAILURE -1
#define CMD_EXIT_MISSING_ARG -2

int execute_cmd_ex(ARCH);
int execute_cmd_testcmd(char*);
int execute_cmd_lm(ARCH, char*);
int execute_cmd_lr(ARCH, char*);
int execute_cmd_dr(ARCH, char *);