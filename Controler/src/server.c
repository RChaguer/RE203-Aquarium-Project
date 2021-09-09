#include <stdio.h>
#include <stdint.h>
#include <string.h> //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> //close
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <time.h>
#include <pthread.h> //for threading , link with lpthread
#include <fcntl.h>
#include "list.h"
#include "config_parser.h"
#include "client.h"
#include "myqueue.h"
#include "server.h"
#include "prompt.h"
#include "aquarium.h"
#include "prompt.h"
#include "protocol.h"
#include <semaphore.h>
#include <signal.h>

#define THREAD_POOL_SIZE 8
#define SOCK_PATH "/tmp/echo_socket"
#define READ_BUFFER_SIZE 100
#define WRITE_BUFFER_SIZE 1024

void error(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
FILE* server_log;
fd_set ready_sockets, current_sockets;
sem_t sem_clients;
int exited = 0;
int max;
list clients;
pthread_t pool[THREAD_POOL_SIZE];
pthread_mutex_t mutex_queue, mutex_sockets;
aquarium *aq;
static struct server_s server;
int max;

void server__init(struct server_s *s, int port)
{
    //création de la socket
    if ((s->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    signal(SIGPIPE, SIG_IGN);
    bzero((char *)&s->address, sizeof(s->address));
    s->address.sin_family = AF_INET;
    s->address.sin_addr.s_addr = INADDR_ANY;
    s->address.sin_port = htons(port);

    //on bind la socket à la structure du serveur
    if (bind(s->socket_fd, (struct sockaddr *)&s->address, sizeof(s->address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void close_connection(client *cl)
{
    FD_CLR(cl->socket_fd, &current_sockets);
    close(cl->socket_fd);
    list__remove(clients, (void *)cl);
    cl = NULL;
}

void *handle_connections(void *arg __attribute__((unused)))
{
    int parser_res = 1;
    char read_buffer[READ_BUFFER_SIZE];
    char *write_buffer = malloc(sizeof(char) * WRITE_BUFFER_SIZE);
    while (!exited)
    {
        parser_res = 1;
        if (sem_trywait(&sem_clients) != 0)
        {
            pthread_mutex_unlock(&mutex_sockets);
            while (sem_trywait(&sem_clients) != 0 && !exited)
            {
            }
        }
        pthread_mutex_lock(&mutex_queue);
        client *cl = dequeue();
        pthread_mutex_unlock(&mutex_queue);
        if (!exited && cl != NULL)
        {
            if (FD_ISSET(cl->socket_fd, &ready_sockets))
            {
                bzero(read_buffer, READ_BUFFER_SIZE);
                int n = read(cl->socket_fd, read_buffer, READ_BUFFER_SIZE);
                bzero(write_buffer, WRITE_BUFFER_SIZE);
                if(n){
                    server_log = fopen("server_log.txt", "a+");
                    if(cl->view != NULL)
                        fprintf(server_log, "%s>> Client N%d: %s\n", get_time(), view__get_id(cl->view), read_buffer);
                    else
                        fprintf(server_log, "%s>> Client Unknown: %s\n", get_time(), read_buffer);
                    fclose(server_log);
                }
                parser_res = protocol__parser(aq, cl, read_buffer, write_buffer);
                if(n){
                    server_log = fopen("server_log.txt", "a+");
                    fprintf(server_log, "<< Server: %s\n", write_buffer);
                    fclose(server_log);
                }
                n = write(cl->socket_fd, write_buffer, strlen(write_buffer));
                if (n == -1)
                {
                    if (errno == EPIPE)
                    {
                        cl->log_out = 1;
                    }
                }
                cl->last_msg = time(NULL);
                if (parser_res == 0 || cl->log_out)
                {
                    close_connection(cl);
                }
            }
            if (parser_res && cl != NULL)
            {
                if ((time(NULL) - cl->last_msg) > get_timeout())
                {
                    close_connection(cl);
                }
                else
                {
                    pthread_mutex_lock(&mutex_queue);
                    enqueue(cl);
                    pthread_mutex_unlock(&mutex_queue);
                }
            }
        }
    }
    pthread_mutex_lock(&mutex_queue);
    client *n1 = dequeue();
    pthread_mutex_unlock(&mutex_queue);
    while (n1 != NULL)
    {
        close_connection(n1);
        pthread_mutex_lock(&mutex_queue);
        n1 = dequeue();
        pthread_mutex_unlock(&mutex_queue);
    }
    free(write_buffer);
    return NULL;
}


client *accept_new_connection(int socket_server)
{
    unsigned int clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    int newclient;
    newclient = accept(socket_server,
                       (struct sockaddr *)&cli_addr, &clilen);
    client *cl = malloc(sizeof(client));
    cl->socket_fd = newclient;
    cl->view = NULL;
    cl->status = 0;
    cl->log_out = 0;
    cl->last_msg = time(NULL);
    strcpy(cl->id,"unknown");
    cl->sendFishes=0;
    return cl;
}

void *server__wait_connections(void *arg __attribute__((unused)))
{
    FD_ZERO(&current_sockets);
    FD_SET(server.socket_fd, &current_sockets);
    struct timeval *timeselect = malloc(sizeof(struct timespec));
    while (!exited)
    {
        pthread_mutex_lock(&mutex_sockets);
        ready_sockets = current_sockets;
        timeselect->tv_sec = 5;
        timeselect->tv_usec = 0;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, timeselect) < 0)
        {
            server_log = fopen("server_log.txt", "a+");
            fprintf(server_log, "%s<< Server Event: select error \n", get_time());
            fclose(server_log);
            perror("select error");
            exit(EXIT_FAILURE);
        }

        int cond = 0;
        int i;
        for (i = 0; i <= max; i++)
        {
            if (FD_ISSET(i, &ready_sockets) && i != server.socket_fd)
            {
                cond++;
                sem_post(&sem_clients);
            }
        }

        if (FD_ISSET(server.socket_fd, &ready_sockets))
        {
            server_log = fopen("server_log.txt", "a+");
            fprintf(server_log, "%s Server Event: New client connected", get_time());
            fclose(server_log);
            client *cl = accept_new_connection(server.socket_fd);
            FD_SET(cl->socket_fd, &current_sockets);
            pthread_mutex_lock(&mutex_queue);
            list__add(clients, cl);
            enqueue(cl);
            pthread_mutex_unlock(&mutex_queue);
            if (cl->socket_fd > max)
            {
                max = cl->socket_fd;
            }
        }
        if (!cond)
        {
            pthread_mutex_unlock(&mutex_sockets);
        }
    }
    free(timeselect);
    return NULL;
}

void *terminal_handler(void *args __attribute__((unused)))
{
    const char *prompt = "$ ";
    char line[1024];

    while (1)
    {
        //read line from terminal
        fprintf(stdout, "%s", prompt);
        bzero(line, 1024);
        fgets(line, 1024, stdin);
        //And then we analyze it
        if (cmd__parser(aq, line) == EXIT)
        {
            exited = 1;
            break;
        }
    }
    return EXIT_SUCCESS;
}

void *aquarium_handler(void *arg __attribute__((unused)))
{
    client *c;
    char server_message[WRITE_BUFFER_SIZE];
    int period = get_update();
    while (!exited && aq != NULL)
    {
        sleep(period);
        if (aquarium__is_loaded(aq))
        {
            aquarium__refresh(aq, period);

            for (int i = 0; i < list__size(clients); i++)
            {
                c = (client *)list__get_from(clients, i);
                if (c->sendFishes)
                {
                    bzero(server_message, WRITE_BUFFER_SIZE);
                    cmd__get_fishes(aq, c, server_message);
                    int send_status = write(c->socket_fd, server_message, strlen(server_message));
                    if (send_status == -1)
                    {
                        if (errno == EPIPE)
                        {
                            c->log_out = 1;
                        }
                    }
                }
            }
        }
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    int parsed = parse_file("controller.cfg");
    if (parsed == 0)
    {
        exit(1);
    }
    int portno = get_port();
    if (portno == -1)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }


    clients = list__init(client__copy, client__compare, client__free);
    aq = aquarium__initialize(1000, 1000);
    server__init(&server, portno);
    max = server.socket_fd;
    if (listen(server.socket_fd, 100) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    sem_init(&sem_clients, 0, max);
    pthread_mutex_init(&mutex_queue, NULL);
    pthread_mutex_init(&mutex_sockets, NULL);
    pthread_create(&pool[0], NULL, terminal_handler, NULL);
    pthread_create(&pool[1], NULL, server__wait_connections, NULL);
    pthread_create(&pool[2], NULL, aquarium_handler, NULL);
    for (int i = 3; i < THREAD_POOL_SIZE; i++)
    {
        pthread_create(&pool[i], NULL, handle_connections, NULL);
    }

    for (int i = 0; i < THREAD_POOL_SIZE; i++)
    {
        void *tmp;
        pthread_join(pool[i], &tmp);
    }
    pthread_mutex_destroy(&mutex_queue);
    pthread_mutex_destroy(&mutex_sockets);
    sem_destroy(&sem_clients);
    close(server.socket_fd);
    list__clear(clients);
    aquarium__free(aq);
    return 0;
}
