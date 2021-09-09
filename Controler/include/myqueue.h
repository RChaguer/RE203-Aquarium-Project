#ifndef MYQUEUE_H_
#define MYQUEUE_H_
#include <stdlib.h>
#include "client.h"
extern size_t size;

struct node {
    struct node* next;
    client *cl;
};
typedef struct node node_t;
extern node_t* head;
extern node_t* tail;
void enqueue(client* cl );
client* dequeue();

#endif