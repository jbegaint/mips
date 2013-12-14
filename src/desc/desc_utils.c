#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

#include "globals.h"
#include "notify.h"

#include "desc/desc.h"
#include "desc/desc_utils.h"

void load_function(void* plugin, void** f, char* f_name)
{
	char* error;
	*f = (void*) dlsym(plugin, f_name);

	if ((error = dlerror()) != NULL)
		fprintf(stderr, "%s\n", error);
}

int load_desc_so(char* plugin_filename, DESC* desc)
{
	void* plugin;
	execute_f execute;
	display_f display;

	plugin = dlopen(plugin_filename, RTLD_LAZY);

	if (!plugin) {
		fprintf(stderr, "%s\n", dlerror());
		return 0;
	}
	else {
		load_function(plugin, (void **) &display, "display");
		desc->display = display;

		load_function(plugin, (void **) &execute, "execute");
		desc->execute = execute;
	}

	return 1;
}

void display_desc_array(void)
{	
	int i;

	for (i = 0; i < DESC_ARRAY_LENGTH; i++) {
		display_desc(DESC_ARRAY[i]);

		if ((i+1)%4 == 0)
			printf("\n");
	}
	if ((i+1)%4 != 0)
		printf("\n");
}

void display_desc(DESC desc)
{
	/* -6: right padding */
	fprintf(stderr, "%-8s", desc.name);
}