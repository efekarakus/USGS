#ifndef _LIST
#define _LIST

/**
 * Node struct that forms the linked list
 */
typedef struct _Node {
	double data;            ///< the data held at the current node
	struct _Node* next;     ///< pointer for the next node
} Node;

/**
 * Singly linked list that holds nodes that contain a double and a next pointer
 */
typedef struct _List {
	struct Node* head; 	///< head of the linked list
} List;

/**
 * Add a new node into the linked list with the value "value"
 * @param list the linked list that we want to insert the new node in
 * @param data the value that we want to insert in the linked list
 */
void insert_node(List* list, double data);

/**
 * Deletes the first occurence of value from the linked list
 * @param list the linked list that we want to remove the data from
 * @param data the value that we want to remove from the linked list
 */
void delete_node(List* list, double data);

/**
 * Deletes the whole linked list and sets list = NULL
 * @param list the linkedlist that we want to free form the memory
 */
void delete_list(List* list);
#endif
