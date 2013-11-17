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

void init_desc_array(void)
{
	DESC desc;
	FILE* f = NULL;
	FILE* f_desc = NULL;
	char desc_filename[256];
	char plugin_filename[80];
	char buffer[256];
	char* filename = "descs/desc.all";
	int c, l = 0;

	DEBUG_MSG("Init desc files parsing");

	f = fopen(filename, "r");
	if (!f)
		exit(EXIT_FAILURE);

	while ((c = getc(f)) != EOF)
		if (c == '\n')
		    l++;
		
	DEBUG_MSG("%d files in list", l);

	/* allocate memory */
	DESC_ARRAY_LENGTH = l;
	DESC_ARRAY = malloc(DESC_ARRAY_LENGTH * sizeof(DESC));

	fseek(f, 0, 0);

	/* parse files */
	c = 0;
	while (fgets(buffer, sizeof(buffer), f) != 0) {
		sscanf(buffer, "%s", buffer);

		strcpy(desc_filename, "descs/");
		strcat(desc_filename, buffer);

		if (is_desc_file(desc_filename)) {

			f_desc = open_file(desc_filename);

			if (f_desc) {
				if (parse_desc_file(f_desc, &desc) == PARSE_SUCCESS) {

					DEBUG_MSG("%s parsing succeeds", desc_filename);

					sprintf(plugin_filename, "descs/%s.so", desc.name);
			
					/* lower str */
					for (int i = 0; plugin_filename[i]; i++)
						plugin_filename[i] = tolower(plugin_filename[i]);
				
					/* open .so */
					if (load_desc_so(plugin_filename, &desc))
						DEBUG_MSG("%s loaded", plugin_filename);

					DESC_ARRAY[c] = desc;

				} 
				else {
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
