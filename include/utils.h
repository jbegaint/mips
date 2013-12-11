#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include "arch/arch.h"

#define UNUSED(x) (void)(x)

int die(ARCH);
int quit(ARCH);
void usage(char*);
FILE* open_file(char*);
void close_file(FILE*);
void print_str(char*, char*, int);
void print_error(char*);
void print_info(char*);
void print_section_info(ARCH);

uint get_hash(char*);
char bin_to_dec(char*);

void swap_str(char**, char**);

void print_logo(void);
void print_bits(uint);
#endif