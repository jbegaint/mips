#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

int cmp_val(void* elt_1, void* elt_2)
{
	/* return elt_1 < elt_2 */
	return (*(unsigned int*) elt_1 < *(unsigned int*) elt_2);
}

list_t add_sort(void* elt, list_t list, size_t size_elt)
{
	list_t new;
	list_t l;

	if (is_list_empty(list) || cmp_val(elt, list->val))
		return add_tail(elt, list, size_elt);

	for (l = list; !is_list_empty(l); l = l->next) {
		if (cmp_val(elt, l->val))
			break;
	}

	new = (list_t) malloc(sizeof(*new));
	new->val = (void*) malloc(size_elt);
	memcpy(new->val, elt, size_elt);

	new->next = l->next;
	l->next = new;

	return list;
}