#include <stdlib.h>

#include "arch.h"

ARCH init_simu(ARCH arch, int mem_size)
{
	/*arch = malloc(sizeof(*arch));
	if (arch == NULL)
		return NULL;

	arch->memory = malloc(mem_size*1024*1024);
	if (arch->memory == NULL)
		return NULL;
	
	return arch;*/
}

void free_arch(ARCH arch)
{
	/*free(arch->memory);*/
	free(arch);
}