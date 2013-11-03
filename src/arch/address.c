#include <stdio.h>
#include <stdlib.h>

#include "arch/arch.h"
#include "arch/address.h"
#include "arch/section.h"

#include "commands.h"
#include "notify.h"
#include "parsers.h"
#include "utils.h"

int get_byte(ARCH arch, uint addr, uchar* val)
{
	int section_index, offset;
	section_index = get_section(arch, addr);

	/* not allocated memory */
	if (section_index == -1)
		return 0;
		
	offset = get_offset(arch, addr, section_index);
	*val = *((arch->sections)[section_index].data + offset);
	
	return 1;
}

int get_byte_info(ARCH arch, uint addr, uchar* val, int* section_index)
{
	int offset;
	*section_index = get_section(arch, addr);

	/* not allocated memory */
	if (*section_index == -1)
		return 0;
		
	offset = get_offset(arch, addr, *section_index);
	*val = *((arch->sections)[*section_index].data + offset);
	
	return 1;
}

int display_byte(ARCH arch, uint addr) 
{
	uchar val;
	int res = get_byte(arch, addr, &val);
	if (res == 1)
		printf("%02x ", val);
	return res;
}

int display_range_addr(ARCH arch, uint addr_start, int bytes_nb)
{
	/* display 16 bytes per line */

	int i;
	int res, section_index;
	int section_index_old = -1;
	uchar val;

	for (i = 0; i < bytes_nb ; i++) {
	    
	    res = get_byte_info(arch, addr_start+i, &val, &section_index);

	    if (section_index != section_index_old && section_index != -1) {
	    	switch (section_index) {
				case TEXT:
					printf("=== section .text ===\n");
					break;

				case BSS:
					printf("\n=== section .bss ===\n");
					break;
				
				case DATA:
					printf("\n=== section .data ===\n");
					break;	
	    	 }
	    	 section_index_old = section_index;
	    }

	    /* print addr */
		if (i%16 == 0 && res) 
	   		printf("%08x: ", addr_start+i);

	   	if (res) 
	   		printf("%02x ", val);
	    
	    if ((i+1)%16 == 0 && res) 
	    	printf("\n");
	}

    printf("\n");

	return CMD_EXIT_SUCCESS;
}

int display_addr(ARCH arch, uint addr)
{
	uint i;

	for (i = 0; i < 4; i++) {
		display_byte(arch, addr + i);
	}
	printf("\n");
	return CMD_EXIT_SUCCESS;
}


int display_addr_to_addr(ARCH arch, char* str_arg)
{
	uint addr0, addr1;
	char* args[2];

	if (parse_args(str_arg, args, 2) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (!parse_addr(args[0], &addr0) || !parse_addr(args[1], &addr1)) {
		print_error("invalid address");
		return CMD_EXIT_INVALID_ADDR;
	}

	if (addr0 > addr1)
		/* or swap maybe ? */
		return CMD_EXIT_ERROR;

	return display_range_addr(arch, addr0, addr1 - addr0);
	    
}

int display_bytes_from_addr(ARCH arch, char* str_arg)
{
	uint addr;
	int bytes_nb;
	char* args[2];

	if (parse_args(str_arg, args, 2) != 1) {
		return CMD_EXIT_MISSING_ARG;
	}

	if (!parse_addr(args[0], &addr)) {
		print_error("invalid address");
		return CMD_EXIT_INVALID_ADDR;
	}

	if (sscanf(args[1], "%d", &bytes_nb) != 1) {
		print_error("Invalid bytes range");
		return CMD_EXIT_FAILURE;
	}

	if (bytes_nb < 0) {
		WARNING_MSG("invalid number (positive expected)");
		return CMD_EXIT_ERROR;
	}

	return display_range_addr(arch, addr, bytes_nb);
}

int display_one_addr(ARCH arch, char* str_arg)
{
	char* args[1];
	uint addr;
	uchar val;

	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

	if (!parse_addr(args[0], &addr)) {
		print_error("invalid address");
		return CMD_EXIT_INVALID_ADDR;
	}

	if (get_byte(arch, addr, &val)) {
		printf("%08x: ", addr);

		for (int j = 0; j < 4; j++) {
			display_byte(arch, addr + j);	
		}
		printf("\n");
	}

	return CMD_EXIT_SUCCESS;
}