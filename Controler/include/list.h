#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>

typedef struct _list * list;
typedef struct _node node;

// Initialize the linked list with the given structure.
list    list__init(void * (*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *));

// Reset the linked list. Context of linked list is deleted.
void    list__reset(list linkedList);

// Clear the linked list. The address must not be used later.
void    list__clear(list linkedList);

// If linked list is empty, 1 returns
int     list__is_empty(const list linkedList);

// Data is added to linked list.
int     list__add(list linkedList, const void * data);

// Data is removed from linked list.
void    list__remove(list linkedList, const void * data);

// Data is removed from index of linked list.
void    list__remove_at(list linkedList, size_t index);

// "data" param is inserted to index of linked list.
int     list__insert(list linkedList, const void * data, size_t index);

//  Data in linked list is taken to "data" param.
void *  list__get_from(const list linkedList, size_t index);

// Address of data in linked list is return.
void *  list__get_address_from(const list linkedList, size_t index);

// Adress of first equal data in linked list is return
void *  list__find(const list linkedlist, void *data);

// Size of linkedlist is returned
size_t  list__size(const list linkedlist);

// Adress of first data in linked list is return
node *  list__get_head(const list linkedlist);

// Adress of next data in linked list is return
node *  node__get_next(const node * n);

#endif /* _LIST_H_ */