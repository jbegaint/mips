#include <ctype.h>
#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "globals.h"

#include "desc/desc.h"
#include "desc/desc_parsers.h"
#include "desc/desc_utils.h"

#include "notify.h"
#include "utils.h"


char* DESC_DIR = "./descs/";
int DESC_ARRAY_LENGTH;
DESC* DESC_ARRAY;

void free_desc_array(void)
{
	free(DESC_ARRAY);
}

void test_init_plugins(void)
{
	void *plugin;
    char filename[80] = "src/instructions/test.so";
    typedef void (*hello_ptr)(void);
    typedef int (*res_ptr)(void);
    hello_ptr hello;
    res_ptr res;
    char* error;

    plugin = dlopen(filename, RTLD_NOW);

    if (!plugin) {
        fprintf(stderr, "%s\n", dlerror());
    }

    *(void**) &hello = dlsym(plugin, "hello");
    if ((error = dlerror()) != NULL)
        fprintf(stderr, "%s\n", error);
    hello();

    *(void**) &res = dlsym(plugin, "res");
    if ((error = dlerror()) != NULL)
        fprintf(stderr, "%s\n", error);
    fprintf(stderr,"RES: %d\n", res());
    

    dlclose(plugin);
}

void init_desc_array(void)
{
	DESC desc;
	FILE* f = NULL;
	FILE* f_desc = NULL;
	char desc_filename[256];
	char* filename = "descs/desc.all";
	int c, l = 0;

	/* plugins stuff */
	char* error;
	char plugin_filename[80];
	display_f display;
	execute_f execute;
	void* plugin;
	/* end plugins stuff */

	DEBUG_MSG("Init desc files parsing");

	/* count desc files in dir */
	/*chdir(DESC_DIR);*/

	f = fopen(filename, "r");
	if (!f)
		exit(EXIT_FAILURE);

	while ((c = getc(f)) != EOF)
		if (c == '\n')
		    l++;
		
	DEBUG_MSG("%d files in list", l);

	/* allocate memory */
	DESC_ARRAY_LENGTH = l - 1;
	DESC_ARRAY = malloc(DESC_ARRAY_LENGTH * sizeof(DESC));

	fseek(f, 0, 0);

	/* parse files */
	c = 0;
	while (fgets(desc_filename, sizeof(desc_filename), f) != 0) {
		sscanf(desc_filename, "%s", desc_filename);

		if (is_desc_file(desc_filename)) {
			chdir(DESC_DIR);
			f_desc = open_file(desc_filename);
			chdir("..");
			if (f_desc) {
				if (parse_desc_file(f_desc, &desc) == PARSE_SUCCESS) {
					DEBUG_MSG("%s parsing succeeds", desc_filename);
					DESC_ARRAY[c] = desc;


					sprintf(plugin_filename, "%s.so", desc.name);
					
					/* lower str */
					for (int i = 0; plugin_filename[i]; i++)
						plugin_filename[i] = tolower(plugin_filename[i]);
				
					plugin = dlopen("descs/add.so", RTLD_NOW);

					if (!plugin) {
						fprintf(stderr, "%s\n", dlerror());
					}
					else {
						*(void**) &display = dlsym(plugin, "display");
						if ((error = dlerror()) != NULL)
								fprintf(stderr, "%s\n", error);

						*(void**) &execute = dlsym(plugin, "execute");
						if ((error = dlerror()) != NULL)
							fprintf(stderr, "%s\n", error);
						desc.display = display;
						desc.execute = execute;
					}

				} else {
					WARNING_MSG("parsing fails for %s", desc_filename);
				}
				close_file(f_desc);
				c++;
			}
		}
	}

	fclose(f);
	
	/*chdir("..");*/

	DEBUG_MSG("End desc files parsing");
}
