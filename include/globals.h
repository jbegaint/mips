#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define PARSING_FILE_EXIT_EOF 3
#define PARSING_FILE_NON_CMD_LINE 2

#include "desc/desc.h"
#include "list.h"

extern list_t BP_LIST;

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;
extern const char* DESC_DIR; 

extern const char* REG_NAMES[36];

#define PC 35

#endif