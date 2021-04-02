#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct _node {
    void *data;
    struct _node *next;
};

struct _list {
    node *head;
    node *tail;
    void *(*dataCreateAndCopy)(const void *);
    int (*dataCompare)(const void *, const void *);
    void (*dataClear)(void *);
};

static void * copyAddress(const void *a) {
    return (void *)a;
}

static int compareAddress(const void *a1, const void *a2) {
    return !(a1 == a2);
}

list list__init(void *(*dataCreateAndCopy)(const void *), int (*dataCompare)(const void *, const void *), void (*dataClear)(void *)) {
    list linkedlist = (list) malloc(sizeof(struct _list));

    if (NULL == linkedlist) {
        perror(NULL);
    } else {
        linkedlist->head = NULL;
        linkedlist->tail = NULL;
        linkedlist->dataCreateAndCopy = (NULL == dataCreateAndCopy) ? copyAddress : dataCreateAndCopy;
        linkedlist->dataCompare = (NULL == dataCompare) ? compareAddress : dataCompare;
        linkedlist->dataClear = (NULL == dataClear) ? free : dataClear;
    }

    return linkedlist;
}

void list__reset(list linkedlist) {
    while (NULL != linkedlist->head)
    {
        node *tmp = linkedlist->head;
        linkedlist->head = tmp->next;
        linkedlist->dataClear(tmp->data);

        free(tmp);
    }

    linkedlist->tail = NULL;
}

void list__clear(list linkedlist) {
    list__reset(linkedlist);
    free(linkedlist);
}

int list__is_empty(const list linkedlist)
{
    return NULL == linkedlist->head;
}

int list__add(list linkedlist, const void *data)
{
    node *iter = linkedlist->head, *tmp;

    if (NULL == (tmp = (node *)malloc(sizeof(node)))) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    if (NULL == (tmp->data = linkedlist->dataCreateAndCopy(data))) {
        free(tmp);
        perror(NULL);
        return EXIT_FAILURE;
    }

    if (NULL == iter) {
        linkedlist->head = tmp;
    }
    else {
        linkedlist->tail->next = tmp;
    }

    tmp->next = NULL;
    linkedlist->tail = tmp;

    return EXIT_SUCCESS;
}

void list__remove(list linkedlist, const void *data)
{
    node *iter = linkedlist->head, *p;

    if (NULL == iter) {
        return;
    }

    if (iter == linkedlist->tail) {
        if (!linkedlist->dataCompare(data, iter->data)) {
            linkedlist->dataClear(iter->data);
            free(iter);
            linkedlist->head = NULL;
            linkedlist->tail = NULL;
        }
        return;
    }

    while (0 != linkedlist->dataCompare(data, iter->data)) {
        if (iter->next == linkedlist->tail) {
            if (!linkedlist->dataCompare(data, iter->next->data)) {
                linkedlist->dataClear(iter->next->data);
                free(iter->next);
                iter->next = NULL;
                linkedlist->tail = iter;
            }
            return;
        }
        iter = iter->next;
    }

    linkedlist->dataClear(iter->data);

    if (iter->next == linkedlist->tail) {
        linkedlist->tail = iter;
    }

    p = iter->next->next;
    iter->data = iter->next->data;

    free(iter->next);
    iter->next = p;
}

void list__remove_at(list linkedlist, size_t index) {
    void *p;
    size_t i;
    node *iter = linkedlist->head;

    if (NULL == iter) {
        return;
    }

    for (i = 0; i < index; i++) {
        if ((iter->next == linkedlist->tail) && ((i + 1) == index)) {
            linkedlist->dataClear(iter->next->data);
            free(iter->next);
            iter->next = NULL;
            linkedlist->tail = iter;

            return;
        }
        if (NULL == iter->next) {
            if (0 == index) {
                linkedlist->dataClear(iter->data);
                free(iter);
                linkedlist->head = NULL;
                linkedlist->tail = NULL;
            }
            return;
        }
        iter = iter->next;
    }

    linkedlist->dataClear(iter->data);

    p = iter->next->next;
    iter->data = iter->next->data;

    free(iter->next);
    iter->next = p;
}

int list__insert(list linkedlist, const void *data, size_t index) {
    size_t i;
    void *p;
    node *iter = linkedlist->head, *tmp = (node *)malloc(sizeof(node));

    if (NULL == tmp) {
        perror(NULL);

        return EXIT_FAILURE;
    }

    if (NULL == (p = linkedlist->dataCreateAndCopy(data))) {
        free(tmp);
        perror(NULL);

        return EXIT_FAILURE;
    }

    for (i = 0; i < index; i++) {
        if (NULL == iter) {
            return EXIT_FAILURE;
        }
        iter = iter->next;
    }

    if (0 == index || NULL == iter) {
        tmp->next = iter;
        iter = tmp;

        if (0 == index) {
            linkedlist->head = tmp;
        }
    }
    else {
        tmp->data = iter->data;
        tmp->next = iter->next;
        iter->next = tmp;
    }

    iter->data = p;

    if (NULL == iter->next) {
        linkedlist->tail = iter;
    }

    return EXIT_SUCCESS;
}

void * list__get_from(const list linkedlist, size_t index) {
    size_t i = 0;
    void *data = NULL;
    node *iter = linkedlist->head;

    while (NULL != iter) {
        if (index == i++) {
            if (NULL == (data = linkedlist->dataCreateAndCopy(iter->data))) {
                perror(NULL);
            }
            break;
        }
        iter = iter->next;
    }
    return data;
}

void * list__get_address_from(const list linkedlist, size_t index) {
    size_t i = 0;
    node *iter = linkedlist->head;

    while (NULL != iter) {
        if (index == i++) {
            return iter->data;
        }
        iter = iter->next;
    }
    return NULL;
}

void * list__find(const list linkedlist, void *data) {
    node *iter = linkedlist->head;

    while (NULL != iter) {
        if (!linkedlist->dataCompare(data, iter->data)) {
            return iter->data;
        }
        iter = iter->next;
    }
    return NULL;
}

size_t list__size(const list linkedlist) {
    size_t i = 0;
    node *iter = linkedlist->head;

    while (NULL != iter) {
        i++;
        iter = iter->next;
    }
    return i;
}

node * list__get_head(const list linkedlist) {
    if (list__is_empty(linkedlist))
        return NULL;
    return linkedlist->head;
}

node * node__get_next(const node * n) {
    if (n != NULL)
        return n->next;
    return NULL;
}