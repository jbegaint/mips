#include <stdio.h>
#include <dirent.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"

#include "notify.h"

void init_desc()
{
	DEBUG_MSG("init desc files");

    DIR *d;
    struct dirent *dir;
    d = opendir("descs/");
   
    if (d) {
        while ((dir = readdir(d))) {
            if (is_desc_file(dir->d_name))
                parse_desc_file(dir->d_name);
        }
       closedir(d);
    }
}