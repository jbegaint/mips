#pragma once

#include "arch.h"

int execute_cmd_ex(ARCH);
int execute_cmd_testcmd(char*);
int execute_cmd_lm(ARCH, char*);

char** get_args(int, char*);