#include "client.h"
#include "view.h"
#include <stdio.h>
#include <string.h>



void *client__copy(const void *c) {
    return (void *) c;
}

int client__compare(const void *c1, const void *c2) {
    return c1 - c2;
}

void client__free(void *c) {
    if (c != NULL) {
        client *_c = (client *) c;
        if (_c->view != NULL) {
            view__disallow(_c->view);
        }
        free(c);
    }
}

void client__connect(client *c) {
    c->status = 1;
}

void client__disconnect(client *c) {
    c->log_out = 1;
    c->status = 0;
    strcpy(c->id, "unknown");
    view__disallow(c->view);
    c->view = NULL;
}

int client__is_connected(client *c) {
    return c->status;
}