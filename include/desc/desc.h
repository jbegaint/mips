#ifndef _DESC_H_
#define _DESC_H_

enum {I, J, R};

typedef struct {
	char name[8]; /* todo: check name lgth in doc */
	char type[1];
	int optcode;
	int function;
} DESC;

void init_desc();

#endif