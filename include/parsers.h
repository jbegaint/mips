#pragma once

/* 
	returns addr in int
*/

int parse_addr(ARCH, char*);

/*
	returns register index between 0 - 31 from string.
	the string can be a register index or a register name, 
		preceded by $ or not.
*/

int parse_register(char*);
