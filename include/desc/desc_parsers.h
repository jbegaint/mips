#ifndef _DESC_PARSERS_H
#define _DESC_PARSERS_H

#define PARSE_SUCCESS 1
#define PARSE_ERROR -1

#include "desc.h"

#include "arch/arch.h"

int is_desc_file(char*);
int parse_desc_file(FILE*, DESC*);
int parse_function(char*, uint*);
int parse_opcode(char*, uint*);
int parse_name(char*, char*);
int parse_type(char*, char*);

#endif
