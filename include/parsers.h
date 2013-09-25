#pragma once

/* 
	returns reg index between 0 - 31 from string.
	the string is the register index or name, 
		it can be preceded with $ or not.
*/
int parse_register(char*);
