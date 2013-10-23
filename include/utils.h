#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include "arch/arch.h"

int die(ARCH);
int quit(ARCH);
void usage(char*);
FILE* open_file(char*);
void close_file(FILE*);
void print_str(char*, char*, int);
void print_error(char*);
void print_info(char*);
void print_section_info(SECTION);

uint get_hash(char*);
char bin_to_dec(char*);

#endif