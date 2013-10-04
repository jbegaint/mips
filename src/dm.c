#include <stdio.h>
#include <stdlib.h>

#include "dm.h"
#include "arch.h"
#include "address.h"
#include "commands.h"
#include "utils.h"
#include "parsers.h"

int display_addr(ARCH arch, uint addr, int nl_flag) 
{
	uint val;
	int section_index, offset;
	section_index = get_section(arch, addr);

	if (section_index == -1) {
		/* not allocated memory */
		printf("00");
		return CMD_EXIT_SUCCESS;
	}
		
	offset = get_offset(arch, addr, section_index);
	val = *((arch->sections)[section_index].data + offset);
	
	printf("%02x", val);

	if (nl_flag)
		printf("\n");
	else
		printf(" ");

	return CMD_EXIT_SUCCESS;
}

int display_one_addr(ARCH arch, char* str_arg)
{
	uint addr;
	char* args[1];

	if (parse_args(str_arg, args, 1) != 1)
		return CMD_EXIT_MISSING_ARG;

	if (!parse_addr(args[0], &addr)) {
		print_error("invalid address");
		return CMD_EXIT_INVALID_ADDR;
	}

	return display_addr(arch, addr, 1);
}

int display_range_addr(ARCH arch, uint addr_start, int bytes_nb)
{
	int i;

	for (i=0; i < bytes_nb ; i++) {
	    
	    if (display_addr(arch, addr_start+i, 0) != 1)
	    	return CMD_EXIT_FAILURE;

	    if ((i+1)%16 == 0) 
	    	printf("\n");
	}

	/* new line in case output did not end on new line */
	if (i%16 != 0) 
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
		return CMD_EXIT_FAILURE;

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

	return display_range_addr(arch, addr, bytes_nb);
}