/*
 * list.c
 * Created by: Tom Loboda
 */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>


void LL_init(List* list)
{
   list->next = NULL;   // Initialize all list members
	list->data = 0;
}

void LL_insert(List* list, double data)
{
	List* first = list->next;

	if (first == NULL)   // if list is empty
	{
		first = (List*)malloc(sizeof(List));
		
		first->data = data;
		first->next = NULL;
		list->next = first;
	}

	else
	{
		List* newNode = (List*)malloc(sizeof(List));
		list->next = newNode;
		
		newNode->data = data;
		newNode->next = first;
	}

}


void LL_insertEnd(List* list, double data)
{
	List* prev = list;
	List* curr = list->next;

	while (curr != NULL)   // Get to the end of the list
	{
		prev = curr;
		curr = curr->next;
	}

	curr = (List*)malloc(sizeof(List));
	prev->next = curr;

	curr->data = data;
	curr->next = NULL;
}

void LL_remove(List* list, double data)
{
	if (LL_isEmpty(list) == 1)
		return;

	List* prev = list;
	List* curr = list->next;

	while (curr->data != data)
	{
		prev = curr;
		curr = curr->next;
		if (curr == NULL)
			return;
	}

	List* link = curr->next;
	prev->next = link;

	free(curr);
	curr = NULL;
}

void LL_print(List* list)
{
	list = list->next;

	while (list != NULL)
	{	
		printf("\n%f", list->data);
		list = list->next;
	}
}

int LL_isEmpty(List* list)
{
	if (list->next == NULL)
		return 1;

	else
		return 0;
}

long LL_count(List* list)
{
	long count = 0;
	list = list->next;

	while (list != NULL)
	{
		count++;
		list = list->next;
	}

	return count;
}

void LL_destroy(List* list)
{
	List* curr = list->next;

	if (curr == NULL)   // No elements in list
		return;

	List* nxt = curr->next;

	if (nxt == NULL)   // Only one element in list
	{
		curr->next = NULL;
		free(curr);
		curr = NULL;
		return;
	}

	int i=0;
	int num = LL_count(list);

	for (i=0; i<num; i++)
	{
		LL_removeFront(list);
	}
}

void LL_removeFront(List* list)
{
	List* prev = list;
	List* curr = list->next;
	List* link = curr->next;

	prev->next = link;

	free(curr);
	curr = NULL;
}
