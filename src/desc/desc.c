#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"
#include "desc/desc_utils.h"

#include "notify.h"
#include "utils.h"

extern DESC* DESC_ARRAY;
extern int DESC_ARRAY_LENGTH;
extern char* DESC_DIR;

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
	char* filename = "desc.all";
	int c, l = 0;

	DEBUG_MSG("Init desc files parsing");

	/* count desc files in dir */
	chdir(DESC_DIR);

	f = fopen(filename, "r");
	if (!f)
		exit(EXIT_FAILURE);

	while ((c = getc(f)) != EOF) {
		if (c == '\n')
		    l++;
	}
	DEBUG_MSG("%d files in list\n", l);

	DESC_ARRAY_LENGTH = l - 1;

	/* allocate memory */
	DESC_ARRAY = malloc(DESC_ARRAY_LENGTH * sizeof(DESC));

	fseek(f, 0, 0);

	c = 0;
	while (fgets(desc_filename, sizeof(desc_filename), f) != 0) {
		sscanf(desc_filename, "%s", desc_filename);

		if (is_desc_file(desc_filename)) {
			f_desc = open_file(desc_filename);

			if (f_desc) {
				if (parse_desc_file(f_desc, &desc) == PARSE_SUCCESS) {
					DEBUG_MSG("%s parsing succeeds", desc_filename);
					DESC_ARRAY[c] = desc;
				}
				close_file(f_desc);
				c++;
			}
		}
	}

	fclose(f);
	
	chdir("..");

	DEBUG_MSG("End desc files parsing");
}
