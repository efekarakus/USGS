/*
 * list.c
 */

#include "list.h"


int main()
{
	List list;	
	LL_init(&list);
//	LL_insert(&list, 10);
//	LL_insert(&list, 20);
//	LL_remove(&list, 20);
//	LL_remove(&list, 10);
//	LL_destroy(&list);	

	LL_print(&list);	
	printf("\nEverything ok!\n");

	return 0;
}


/**
 * Initializes the linked list before use
 * @param list the linked list that will be initialized
 */
void LL_init(List* list)
{
   list = malloc(sizeof(List));
	list->head = NULL;

	if (list->head == NULL)
		printf("\nPass test 1");
}


/**
 * Add a new node into the linked list with the data value
 * @param list the linked list that we want to insert the new node into
 * @param data the double value that we want to insert into the linked list
 */
void LL_insert(List* list, double data)
{
	if (list->head == NULL)   // If list is empty
	{
		list->head = (Node*)malloc(sizeof(Node));
		list->head->data = data;
		list->head->next = NULL;
	}

	else
	{
		Node* link = list->head;
		list->head = (Node*)malloc(sizeof(Node));
		list->head->data = data;
		list->head->next = link;
	}

/*
	List* curr = list;

	if (curr == NULL)   // if list is empty
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
*/
}


/**
 * Add a new node into end of the linked list
 * @param list the linked list that we want to insert the new node into
 * @param data the double value that we want to insert into the end of the linked list
 */
void LL_insertEnd(List* list, double data)
{
/*
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
*/
}


/**
 * Deletes the first occurence of value from the linked list
 * @param list the linked list that we want to remove the data from
 * @param data the value that we want to remove from the linked list
 */
void LL_remove(List* list, double data)
{
/*
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
	rrev->next = link;

	free(curr);
	curr = NULL;
*/
}


/**
 * Deletes the element from the front of the list
 * @param list the linked list that we want to remove the front element from
 */
void LL_removeFront(List* list)
{
/*
	List* prev = list;
	List* curr = list->next;
	List* link = curr->next;

	prev->next = link;

	free(curr);
	curr = NULL;
*/
}


/**
 * Prints out every value in the list
 * @param list the linked list that we want to print
 */
void LL_print(List* list)
{
	Node* curr = list->head;

	if (curr == NULL)
		printf("\nshould be null...");
	else {
		printf("%f data", curr->data);
	}
/*
	while (curr != NULL)
	{	
		printf("\n%f", curr->data);
			
		if (curr->next == NULL)
			printf("\nNO!!!");

		curr = curr->next;
	}
*/
}


/**
 * Determines whether or not the list is empty
 * @param list the linked list that we want to check for emptiness
 * @return 0 if the list is not empty and 1 if it is
 */
int LL_isEmpty(List* list)
{
/*
	if (list->next == NULL)
		return 1;

	else
		return 0;
*/
}


/**
 * Determines the number of elements in the list
 * @param list the linked list that we want to query
 * @return the number of elements in the list
 */
long LL_count(List* list)
{
/*
	long count = 0;
	list = list->next;

	while (list != NULL)
	{
		count++;
		list = list->next;
	}

	return count;
*/
}


/**
 * Deletes the whole linked list and frees all allocated memory
 * @param list the linked list that we want to free from memory
 */
void LL_destroy(List* list)
{
/*
	List* curr = list->next;

	if (curr == NULL)   // No elements in list
	{
		free(list);
		list = NULL;
		return;
	}

	printf("1\n");	

	List* nxt = curr->next;

	if (nxt == NULL)   // Only one element in list
	{
		curr->next = NULL;
		free(curr);
		curr = NULL;
		free(list);
		list = NULL;
		return;
	}

	printf("2\n");

	int i=0;
	int num = LL_count(list);

	for (i=0; i<num; i++)
	{
		LL_removeFront(list);
	}

	printf("3\n");

	free(list);
	list = NULL;
*/
}
