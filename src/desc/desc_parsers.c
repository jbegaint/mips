#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "desc/desc.h"
#include "desc/desc_parsers.h"

#include "utils.h"
#include "notify.h"

int parse_type(char* str, char* type)
{
	if (strlen(str) != 1)
		return PARSE_ERROR;

	if (*str != 'I' && *str != 'J' && *str != 'R')
		return PARSE_ERROR;
	
	if (sscanf(str, "%s", type) != 1)
		return PARSE_ERROR;

	return PARSE_SUCCESS;
}

int parse_name(char* str, char* name)
{
	uint i;

	for (i=0; i < strlen(str); i++) {
		if (!isalpha(*(str+i)))
			return PARSE_ERROR;
	}

	if (sscanf(str, "%s", name) != 1)
		return PARSE_ERROR;

	return PARSE_SUCCESS;
}

int parse_optcode(char* str, int* optcode)
{
	uint i;

	if (strlen(str) != 6)
		return PARSE_ERROR;

	for (i=0; i < 6; i++) {
		if (!isdigit(*(str+i)))
			return PARSE_ERROR;
	}

	if (sscanf(str, "%d", optcode) != 1)
		return PARSE_ERROR;

	return PARSE_SUCCESS;
}

int parse_function(char* str, int* function)
{
	/* idem, 6 binary digits */
	return parse_optcode(str, function);
}


int parse_desc_file(char* filename, DESC* desc)
{
    int c = 0;
    char* value;
    char line[256], buffer[256];
    FILE* f = NULL;

    f = open_file(filename);

    if (f == NULL)
	    return PARSE_ERROR;

    while (fgets(line, sizeof(line), f) != 0 && c < 4) {

    	if (sscanf(line, "%s", buffer) != 1)
    		return PARSE_ERROR;

    	value = strchr(buffer, '=');

    	if (!(value && strlen(value) > 1))
    		return PARSE_ERROR;

    	value++;

    	switch (c) {
	    	case 0:
	    		if (parse_name(value, desc->name))
    				fprintf(stderr, "%s\n", desc->name);
	    		break;

	    	case 1:
    			if (parse_type(value, desc->type))
    				fprintf(stderr, "%s\n", desc->type);
	    		break;

	    	case 2:
		    	if (parse_optcode(value, &(desc->optcode)))
	    				fprintf(stderr, "%06d\n", desc->optcode);
		    		break;

		    case 3:
		    	if (*(desc->type) == 'R') {
		    		if (parse_function(value, &(desc->function)))
	    				fprintf(stderr, "%06d\n", desc->function);
		    	}			
    	}
    	c++;
    }

    close_file(f);

    return PARSE_SUCCESS;
}

int is_desc_file(char* filename)
{
    char* ext;
    ext = strrchr(filename, '.');
    if (ext) {
        if (strcmp(ext + 1, "desc"))
            return 0;
    }
    return 1;
}
