#ifndef _LIST
#define _LIST

#include <stdio.h>
#include <stdlib.h>

/**
 * Singly linked list struct that has a data field and a pointer to a next node
 * (Contains dummy head node)
 */
typedef struct _List {
   struct _List* next;
   double data;
} List;


/**
 * Initializes the linked list before use
 * @param list the linked list that will be initialized
 */
void LL_init(List* list);


/**
 * Add a new node into the linked list with the data value
 * @param list the linked list that we want to insert the new node into
 * @param data the double value that we want to insert into the linked list
 */
void LL_insert(List* list, double data);


/**
 * Add a new node into end of the linked list
 * @param list the linked list that we want to insert the new node into
 * @param data the double value that we want to insert into the end of the linked list
 */
void LL_insertEnd(List* list, double data);


/**
 * Deletes the first occurence of value from the linked list
 * @param list the linked list that we want to remove the data from
 * @param data the value that we want to remove from the linked list
 */
void LL_remove(List* list, double data);


/**
 * Deletes the element from the front of the list
 * @param list the linked list that we want to remove the front element from
 */
void LL_removeFront(List* list);


/**
 * Prints out every value in the list
 * @param list the linked list that we want to print
 */
void LL_print(List* list);

/**
 * Determines whether or not the list is empty
 * @param list the linked list that we want to check for emptiness
 * @return 0 if the list is not empty and 1 if it is
 */
int LL_isEmpty(List* list);


/**
 * Determines the number of elements in the list
 * @param list the linked list that we want to query
 * @return the number of elements in the list
 */
long LL_count(List* list);


/**
 * Deletes the whole linked list and frees all allocated memory
 * @param list the linked list that we want to free from memory
 */
void LL_destroy(List* list);
#endif
