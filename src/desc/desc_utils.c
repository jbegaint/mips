#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "notify.h"

#include "desc/desc.h"
#include "desc/desc_utils.h"

int load_desc_so(char* plugin_filename, DESC* desc)
{
	char* error;
	void* plugin;
	execute_f execute;
	display_f display;

	plugin = dlopen(plugin_filename, RTLD_LAZY);

	if (!plugin) {
		fprintf(stderr, "%s\n", dlerror());
		return 0;
	}
	else {
		
		*(void**) &display = dlsym(plugin, "display"); 

		if ((error = dlerror()) != NULL)
			fprintf(stderr, "%s\n", error);
		else
			desc->display = display;

		*(void**) &execute = dlsym(plugin, "execute");

		if ((error = dlerror()) != NULL)
			fprintf(stderr, "%s\n", error);
		else
			desc->execute = execute;
	}

	return 1;
}

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