#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h> 
#include <sys/socket.h>
#include <pthread.h>
#include "view.h"
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>

typedef struct {
    struct sockaddr_in client_socket;
    time_t last_msg;
    char id[20];
    struct _view* view;
    int socket_fd;
    int status;
    int sendFishes;
    int log_out;
} client;


client*     client__initialize     ();
int         client__compare        (const void *c1, const void *c2);
void        client__free           (void *c);
void *      client__copy           (const void *c);
void        client__connect        (client *c);
void        client__disconnect     (client *c);
int         client__is_connected   (client *c);
#endif