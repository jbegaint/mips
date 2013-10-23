#ifndef _DESC_PARSERS_H
#define _DESC_PARSERS_H

#define PARSE_SUCCESS 1
#define PARSE_ERROR -1

#include "desc.h"

int is_desc_file(char*);
int parse_desc_file(FILE*, DESC*);
int parse_function(char*, int*);

#endif
