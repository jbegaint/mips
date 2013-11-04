#include <stdio.h>

#include "desc/desc.h"
#include "desc/desc_utils.h"

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;

void display_desc_array(void)
{	
	int i;
	for (i = 0; i < DESC_ARRAY_LENGTH; i++) {
		/* -6 : right padding */
		/*fprintf(stderr, "%-6s", DESC_ARRAY[i].name);*/
		display_desc(DESC_ARRAY[i]);
		if ((i+1)%4 == 0)
			printf("\n");
	}
	if ((i+1)%4 != 0)
			printf("\n");
}

void display_desc(DESC desc)
{
	fprintf(stderr, "%-6s", desc.name);
	fprintf(stderr, "%c\n", desc.type);
	fprintf(stderr, "%06d\n", desc.opcode);
	fprintf(stderr, "%06d\n", desc.function);
}