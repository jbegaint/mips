#ifndef _DESC_H_
#define _DESC_H_

enum INSTRUCTION_TYPE {I, J, R};

typedef struct {
	char name[8]; /* check longest name in doc */
	INSTRUCTION_TYPE type;
	char optcode;
	char function;
} DESC;

#endif