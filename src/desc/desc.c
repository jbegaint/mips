#include <stdio.h>
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
	int c = 0;
	int cc = 0;

	DIR *d;
	DESC desc;
	struct dirent *dir;
	char* filename;

	FILE* f = NULL;

	DEBUG_MSG("Init desc files parsing");

	/* count desc files in dir */
	chdir(DESC_DIR);
	d = opendir("./");
	if (d) {
		while ( (dir = readdir(d)) ) {
			if (is_desc_file(dir->d_name)) {
				f = open_file(dir->d_name);
				if (f) {   					
					if (parse_desc_file(f, &desc) == PARSE_SUCCESS) {
						cc++;
					}
					close_file(f);
				}
			}
		}
		closedir(d);
	}	
	DESC_ARRAY_LENGTH = cc;

	/* allocated memory */
	DESC_ARRAY = malloc(DESC_ARRAY_LENGTH*sizeof(DESC));

	/* fill array */
	chdir(DESC_DIR);
	d = opendir("./");

	if (d) {
		while ( (dir = readdir(d)) ) {
			filename = dir->d_name;

			if (is_desc_file(filename)) {
				f = open_file(filename);
				if (f == NULL) {
	   				WARNING_MSG("Error opening %s", filename);
	   			}
   				else {   					
					if (parse_desc_file(f, &desc) == PARSE_SUCCESS) {
						DESC_ARRAY[c] = desc;
						DEBUG_MSG("%s parsing succeeds", filename);
					}
					else {
						char err[256];
						sprintf(err, "%s parsing fails", filename);
						print_error(err);
					}
					close_file(f);
				}
				c++;
			}
		}
		DEBUG_MSG("Found %d desc file%s", c, ((c > 1)? "s":""));
		closedir(d);
	}

	chdir("../");   
	DEBUG_MSG("End desc files parsing");
}