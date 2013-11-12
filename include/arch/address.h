#ifndef _ADDRESS_H_
#define _ADDRESS_H_

#include "arch.h"

#define BYTE_ALLOCATED 1
#define BYTE_NOT_ALLOCATED 0

int display_addr(ARCH, uint);
int display_byte(ARCH, uint);
int display_range_addr(ARCH, uint, int);

int get_byte(ARCH, uint, uchar*);
int get_byte_details(ARCH, uint, uchar*, int*);

int display_addr_to_addr(ARCH, char**);
int display_bytes_from_addr(ARCH, char**);
int display_one_addr(ARCH, char**);

#endif