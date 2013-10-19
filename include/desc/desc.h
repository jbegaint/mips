#ifndef _DESC_H_
#define _DESC_H_

enum TYPE {I, J, R};

typedef struct {
	char name[8]; /* check longest name in doc */
	enum TYPE type;
	char optcode;
	char function;
} DESC;

void init_desc();

#endif