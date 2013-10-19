#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "notify.h"

int parse_desc_file(char* filename)
{
    printf("HELLO WORLD\n");
    FILE* f = NULL;
    f = open_file(filename);

    if (f == NULL)
        return 1;

    char line[256];
	/*memset(line, '\0', 256);*/
    if (fgets(line, sizeof(line), f) != 0) {
    	printf("%s\n", line);
    }

    close_file(f);
    return 0;
}

int is_desc_file(char* filename)
{
    char* ext;
    ext = strrchr(filename, '.');
    if (ext) {
        if (strcmp(ext+1, "desc"))
            return 0;
    }
    return 1;
}
