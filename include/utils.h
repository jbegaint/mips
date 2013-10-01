#pragma once

#include <stdio.h>
#include "arch.h"

int die(ARCH);
int quit(ARCH);
void usage(char*);
FILE* open_file(char*);
void print_str(char*, char*, int);
void print_error(char*);
void print_info(char*);
void print_section_info(SECTION);
