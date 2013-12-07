#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

typedef struct list_elt {
	void* val;
	struct list_elt *next;
} *list_t;

list_t init_list(void);
list_t add_head(void*, list_t, size_t);
list_t add_sort(void*, list_t, size_t);
list_t add_tail(void*, list_t, size_t);
list_t del_head(list_t);
list_t del_elt_n(list_t, int);

void free_elt(list_t);
void free_list(list_t);

int cmp_val_int(void*, void*);
int find_elt_int(void*, list_t);
int is_list_empty(list_t);

void display_list(list_t);

#endif