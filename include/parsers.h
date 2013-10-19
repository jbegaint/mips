#pragma once

/*
	returns 1 if no error, value in ptr
*/
int parse_hex_value(char*, uint*, uint);

/* 
	returns address value in addr, and boolean status
*/

int parse_addr(char*, uint*);

/* 
	same fct, as a reg containes 32 bits..
*/

int parse_reg_value(char*, uint*);

/*
	return addr value
*/
int parse_addr_value(char*, uchar*);

/*
	returns register index between 0 - 31 from string.
	the string can be a register index or a register name, 
		preceded by $ or not.
*/

int parse_register(char*);

/*
	returns args from str in string array
*/
int parse_args(char*, char**, int);
