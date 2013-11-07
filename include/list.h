#ifndef _LIST_H_
#define _LIST_H_

typedef struct list_elt {
	void* val;
	struct list_elt *next;
} *list_t;

int is_list_empty(list_t);
int cmp_val(void*, void*);
list_t add_head(void*, list_t, size_t);
list_t add_sort(void*, list_t, size_t);
list_t add_tail(void*, list_t, size_t);
list_t del_head(list_t);
void display_list(list_t);

#endif