#pragma once

#include "arch.h"

int display_addr(ARCH, uint, char);
int display_one_addr(ARCH, char*);
int display_addr_to_addr(ARCH, char*);
int display_bytes_from_addr(ARCH, char*);
int display_range_addr(ARCH, uint, int);