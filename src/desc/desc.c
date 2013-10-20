#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"

#include "notify.h"
#include "utils.h"

extern DESC* DESC_ARRAY;
extern char* DESC_DIR;

void free_desc(void)
{
	/*free(DESC_ARRAY);*/
}

void init_desc(void)
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
			if (is_desc_file(dir->d_name))
				cc++;
		}
		closedir(d);
	}	

	/* allocated memory */
	DESC_ARRAY = malloc(cc*sizeof(DESC));

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
						/*memcpy(DESC_ARRAY+c, &desc, sizeof(DESC));*/
						DEBUG_MSG("%s parsing succeeds", filename);
					}
					else {
						char err[256];
						sprintf(err, "%s parsing fails", filename);
						print_error(err);
					}
					close_file(f);
				}
				printf("%s\n", DESC_ARRAY[c].name);
				c++;
			}
		}
		DEBUG_MSG("Found %d desc file%s", c, ((c > 1)? "s":""));
		closedir(d);
	}

	chdir("../");   
	DEBUG_MSG("End desc files parsing");
}