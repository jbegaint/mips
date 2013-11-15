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
		return BYTE_NOT_ALLOCATED;
		
	offset = get_offset(arch, addr, section_index);
	*val = *((arch->sections)[section_index].data + offset);
	
	return BYTE_ALLOCATED;
}

int get_byte_details(ARCH arch, uint addr, uchar* val, int* section_index)
{
	int offset;
	*section_index = get_section(arch, addr);

	/* not allocated memory */
	if (*section_index == -1)
		return BYTE_NOT_ALLOCATED;
		
	offset = get_offset(arch, addr, *section_index);
	*val = *((arch->sections)[*section_index].data + offset);
	
	return BYTE_ALLOCATED;
}

int display_byte(ARCH arch, uint addr) 
{
	uchar val;
	int res = get_byte(arch, addr, &val);
	if (res)
		printf("%02x ", val);
	return res;
}

/**
@brief display bytes (16 per line)
@param ARCH arch 
@param addr_start display bytes from 
@param bytes_nb to
*/

int display_range_addr(ARCH arch, uint addr_start, int bytes_nb)
{
	int i;
	uint c = 0;
	int res;
	int section_index = -1;
	int section_index_old = -1;
	uchar val;

	for (i = 0; i < bytes_nb ; i++) {

		/* skip to next section, if what remains is empty */
		if (section_index != -1 && section_index < 2) {
			if (c  == (arch->sections[section_index]).size) {
	
				fprintf(stderr, "SECTION index %d %d\n", section_index, i);
				getchar();

				i = arch->sections[section_index+1].start_addr - 1;
				c = 0;
				continue; 
			}
		}	

		/* get all details on byte */
		res = get_byte_details(arch, addr_start + i, &val, &section_index);
	    
	    if (section_index != section_index_old && section_index >= 0) {
	    	switch (section_index) {
				case TEXT:
					printf("=== section .text");
					break;

				case BSS:
					printf("\n=== section .bss");
					break;
				
				case DATA:
					printf("\n=== section .data");
					break;	
	    	 }
		    if (arch->sections[section_index].size < (uint) bytes_nb - i)
		    	printf(" (%d", arch->sections[section_index].size);
		    else
		    	printf(" (%d", bytes_nb - i);

		    printf(" bytes) ===\n");

	    	section_index_old = section_index;	
	    }

	    if (res) {
	    	/* print addr */
			if (i%16 == 0) 
		   		printf("%08x: ", addr_start+i);

		   	/* print value */
	   		printf("%02x ", val);
		    
		    /* break line */
		    if ((i+1)%16 == 0) 
		    	printf("\n");
		}

		/* increment section-bytes counter */
	    c++;
	}

    printf("\n");

	return CMD_EXIT_SUCCESS;
}

int display_addr(ARCH arch, uint addr)
{
	uint i;

	for (i = 0; i < 4; i++)
		display_byte(arch, addr + i);

	printf("\n");
	return CMD_EXIT_SUCCESS;
}


int display_addr_to_addr(ARCH arch, char** args)
{
	uint addr0, addr1;

	if (!parse_addr(args[0], &addr0) || !parse_addr(args[2], &addr1))
		return CMD_EXIT_INVALID_ADDR;

	if (addr0 > addr1)
		/* or swap maybe ? */
		return CMD_EXIT_ERROR;

	return display_range_addr(arch, addr0, (addr1 - addr0 + 1));
	    
}

int display_bytes_from_addr(ARCH arch, char** args)
{
	uint addr;
	int bytes_nb;

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (sscanf(args[2], "%d", &bytes_nb) != 1) {
		print_error("Invalid bytes range");
		return CMD_EXIT_ERROR;
	}

	if (bytes_nb < 0) {
		WARNING_MSG("invalid number (positive expected)");
		return CMD_EXIT_ERROR;
	}

	return display_range_addr(arch, addr, bytes_nb);
}

int display_one_addr(ARCH arch, char** args)
{
	uint addr;
	uchar val;

	if (!parse_addr(args[0], &addr))
		return CMD_EXIT_INVALID_ADDR;

	if (get_byte(arch, addr, &val)) {
		printf("%08x: ", addr);

		for (int j = 0; j < 4; j++) {
			display_byte(arch, addr + j);	
		}
		printf("\n");
	}

	return CMD_EXIT_SUCCESS;
}