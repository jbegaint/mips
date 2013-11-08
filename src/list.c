#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "list.h"

int is_list_empty(list_t l)
{
	return !l;
}

list_t add_head(void* elt, list_t head, size_t size_elt) 
{
	list_t new;
	new = (list_t) malloc(sizeof(*new));

	if (new == NULL)
		return NULL;

	new->val = (void*) malloc(size_elt);

	memcpy(new->val, elt, size_elt);

	new->next = head;
	return new;
}

list_t add_tail(void* elt, list_t list, size_t size_elt)
{
	list_t new;
	list_t l;

	new = (list_t) malloc(sizeof(*new));

	if (new == NULL)
		return NULL;

	new->val = (void*) malloc(size_elt);

	if (new->val == NULL)
		return NULL;

	new->next = NULL;

	memcpy(new->val, elt, size_elt);

	if (!(is_list_empty(list))) {
		for (l = list; !is_list_empty(l); l = l->next) {
			if (is_list_empty(l->next))
				break;
		}
		l->next = new;
		return list;
	}
	return new;
}

list_t del_head(list_t head)
{
	list_t new;

	if (is_list_empty(head))
		return NULL;

	new = (list_t) malloc(sizeof(*new));

	if (new == NULL)
		return NULL;

	new = head->next;
	free(head);

	return new;
}

list_t add_sort(void* elt, list_t list, size_t size_elt)
{
	list_t new;
	list_t l;

	if (is_list_empty(list) || cmp_val_int(elt, list->val))
		return add_head(elt, list, size_elt);

	for (l = list; !is_list_empty(l->next); l = l->next) {
		if (cmp_val_int(elt, l->next->val))
			break;
	}

	new = (list_t) malloc(sizeof(*new));
	new->val = (void*) malloc(size_elt);
	memcpy(new->val, elt, size_elt);

	new->next = l->next;
	l->next = new;

	return list;
}

void display_list(list_t list)
{
	list_t l;

	if (!is_list_empty(list)) {
		for (l = list; !is_list_empty(l); l = l->next) {
			printf("0x%08x ", *(uint32_t*) l->val);
		}
	}

	printf("\n");
}

int cmp_val_int(void* elt_1, void* elt_2)
{
	if (*(uint32_t*) elt_1 < *(uint32_t*) elt_2) 
		return 1;
	else if (*(uint32_t*) elt_1 == *(uint32_t*) elt_2)
		return 2;
	return 0;
}

int find_elt_int(void* elt, list_t list)
{
	int i = 0;

	if (is_list_empty(list))
		return -1;

	for (list_t l = list; !is_list_empty(l); l = l->next) {
		if (cmp_val_int(elt, l->val) == 2)
			return i;
		i++;
	}

	return -1;
}

list_t del_elt_n(list_t list, int n)
{
	list_t l, tmp;
	int i = 0;

	if (n == 0)
		return del_head(list);

	for (l = list; !is_list_empty(l); l = l->next) {
		if (i == n - 1) 
			break;
		i++;
	}

	tmp = l->next;
	l->next = tmp->next;
	free(tmp);
	
	return list;
}