#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"

#include "notify.h"
#include "utils.h"

void init_desc()
{
	int c = 0;
	DIR *d;
	DESC desc;
	struct dirent *dir;
	char* desc_dir = "./descs/";
	char* filename;

	FILE* f = NULL;

	DEBUG_MSG("Init desc files parsing");

	chdir(desc_dir);
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
					if (parse_desc_file(f, &desc) == PARSE_SUCCESS)
						DEBUG_MSG("%s parsing succeeds", filename);
					else {
						char err[256];
						sprintf(err, "%s parsing fails", filename);
						print_error(err);
					}
				}
				close_file(f);
				c++;
			}
		}
		DEBUG_MSG("Found %d desc file%s", c, ((c > 1)? "s":""));
		closedir(d);
	}

	chdir("../");   
	DEBUG_MSG("End desc files parsing");
}