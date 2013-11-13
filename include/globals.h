#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "desc/desc.h"
#include "list.h"
#include "run.h"
#include "simMips.h"

#define PARSING_FILE_EXIT_EOF 3
#define PARSING_FILE_NON_CMD_LINE 2


/* global variables */
extern struct command cmd_table[];

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;
extern char* DESC_DIR; 
extern char* REG_NAMES[36];

#endif