#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"

#include "notify.h"

void init_desc()
{
	int c = 0;
	DIR *d;
	struct dirent *dir;
	char* desc_dir = "./descs/";
	char* filename;

	DEBUG_MSG("init desc files");

	chdir(desc_dir);
	d = opendir("./");

	if (d) {
		while ((dir = readdir(d))) {

			filename = dir->d_name;

			if (is_desc_file(dir->d_name)) {
				c++;

				if (parse_desc_file(filename) == PARSE_SUCCESS)
					DEBUG_MSG("%s parsing succeeds", filename);
				else
					WARNING_MSG("%s parsing fails", filename);
			}
		}
		DEBUG_MSG("Found %d desc file%s", c, ((c > 1)? "s":""));
		closedir(d);
	}

	chdir("../");   
}