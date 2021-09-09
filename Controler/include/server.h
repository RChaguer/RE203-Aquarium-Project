#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

struct server_s{
    struct sockaddr_in address;
    int socket_fd;

};

void server__init(struct server_s* s, int port);

#endif 