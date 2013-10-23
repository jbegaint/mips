#include <stdio.h>

#include "desc/desc.h"
#include "desc/desc_utils.h"

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;

void display_desc_array(void)
{	
	int i;
	for (i=0; i < DESC_ARRAY_LENGTH; i++) {
		printf("%d\n", i);
		display_desc(DESC_ARRAY[i]);
		fprintf(stderr, "%s\n", "--------");
	}
}

void display_desc(DESC desc)
{
	fprintf(stderr, "%s\n", desc.name);
	fprintf(stderr, "%c\n", desc.type);
	fprintf(stderr, "%06d\n", desc.opcode);
	fprintf(stderr, "%06d\n", desc.function);
}