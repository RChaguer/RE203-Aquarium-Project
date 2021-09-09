#include "myqueue.h"

node_t* head = NULL;
node_t* tail = NULL;
size_t size=0;

void enqueue(client* cl) {
    node_t *newnode = malloc(sizeof(node_t));
    newnode->cl = cl;
    newnode->next = NULL;
    if (tail == NULL) {
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;
    size++;
} 

client* dequeue() {
    if (head == NULL) {
        return NULL;
    } else {
        client *result = head->cl;
        node_t *temp = head;
        head = head->next;
        if (head == NULL) {tail = NULL;}
        free(temp);
        size--;
        return result;
    }
}