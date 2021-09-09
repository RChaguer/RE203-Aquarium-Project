#include "aquarium.h"
#include "protocol.h"
#include "mobility.h"
#include "client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int starts_with(const char *str, const char *pre)
{
    size_t lenpre = strlen(pre),
           lenstr = strlen(str);
    return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

int equals(const char *str, const char *cmd)
{
    return !strcmp(str, cmd);
}

int protocol__parser(aquarium *aq, client *c, char *msg, char *answer)
{
    if (starts_with(msg, "hello"))
    {
        cmd__greeting(aq, c, msg, answer);
    }
    else if (client__is_connected(c))
    {
        if (starts_with(msg, "ping"))
        {
            cmd__ping(aq, c, msg, answer);
        }
        else if (starts_with(msg, "getFishesContinuously"))
        {
            cmd__get_fishes_continuously(aq, c, answer);
        }
        else if (starts_with(msg, "getFishes"))
        {
            cmd__get_fishes(aq, c, answer);
        }
        else if (starts_with(msg, "addFish"))
        {
            cmd__addFish(aq, c, msg, answer);
        }
        else if (starts_with(msg, "delFish"))
        {
            cmd__delFish(aq, c, msg, answer);
        }
        else if (starts_with(msg, "startFish"))
        {
            cmd__startFish(aq, c, msg, answer);
        }
        else if (starts_with(msg, "log"))
        {
            cmd__log(aq, c, answer);
            return 0;
        }
        else
        {
            cmd__undefined(aq, c, answer);
        }
    }
    return 1;
}

void cmd__greeting(aquarium *aq, client *c, char *msg, char *answer)
{
    if (!client__is_connected(c))
    {

        if (equals(msg, "hello"))
        {
            c->view = aquarium__get__free_view(aq, -1);
        }
        else
        {
            int id = -1;
            sscanf(msg, "hello in as N%d\n", &id);
            c->view = aquarium__get__free_view(aq, id);

            if (c->view == NULL)
            {
                c->view = aquarium__get__free_view(aq, -1);
            }
        }
        if (c->view != NULL)
        {
            char client_id[20];
            sprintf(client_id, "N%d", c->view->id);
            strcpy(c->id, client_id);
            client__connect(c);
            char respond[64];
            sprintf(respond, "greeting N%d\n", view__get_id(c->view));
            strcat(answer, respond);
        }
        else
        {
            strcat(answer, "No greeting\n");
        }
    }
    else
    {
        char respond[64];
        sprintf(respond, "Already greeted N%d\n", view__get_id(c->view));
        strcat(answer, respond);
    }
}

void cmd__ping(aquarium *aq, client *c, char *msg, char *answer)
{
    char respond[64];
    sscanf(msg, "ping %s", respond);
    strcat(answer, "pong ");
    strcat(answer, respond);
    strcat(answer, "\n");
}

void cmd__get_fishes(aquarium *aq, client *c, char *answer)
{
    fish *f;
    size_t size = list__size(aq->fishes);
    strcat(answer, "list ");
    for (size_t i = 0; i < size; i++)
    {
        f = (fish *)list__get_address_from(aq->fishes, i);
        if (f->state)
            fish__get_view_destination(c->view, f, answer);
    }
    strcat(answer, "\n");
}

void cmd__addFish(aquarium *aq, client *c, char *msg, char *answer)
{
    char *name = malloc(64 * sizeof(char));
    char type[64];
    strcpy(type, "");
    coord_float coord;
    int b_w, b_h, x, y;
    int ret = sscanf(msg, "addFish %s at %dx%d, %dx%d, %s\n", name, &x, &y, &b_w, &b_h, type);

    mobility_type m = set__mobility__type(type);

    if (ret != 6)
    {
        free(name);
        strcat(answer, "NOK : Erreur de synthaxe addFish\n");
        return;
    }

    if (m == Error)
    {
        free(name);
        strcat(answer, "NOK : Modèle de mobilité non supporté\n");
        return;
    }

    if (aquarium__find_fish(aq, name))
    {
        free(name);
        strcat(answer, "NOK : Poisson déjà dans l'aquarium\n");
        return;
    }
    coord.x = x * (c->view->d.width / 100);
    coord.y = y * (c->view->d.height / 100);
    coord_float global_coord = view__get_global_coord(c->view, &coord);
    fish *f = fish__initialize(name, b_w, b_h, global_coord.x, global_coord.y, m, aq->dim);
    aquarium__add_fish(aq, f);
    strcat(answer, "OK\n");
    return;
}

void cmd__delFish(aquarium *aq, client *c, char *msg, char *answer)
{
    char name[64];
    sscanf(msg, "delFish %s\n", name);
    if (aquarium__delete_fish(aq, name))
    {
        strcat(answer, "OK\n");
        return;
    }
    strcat(answer, "NOK : Poisson inexistant\n");
    return;
}

void cmd__startFish(aquarium *aq, client *c, char *msg, char *answer)
{
    char name[64];
    sscanf(msg, "startFish %s\n", name);
    fish *f = aquarium__find_fish(aq, name);
    if (f != NULL)
    {
        fish__start(f);
        strcat(answer, "OK\n");
        return;
    }
    strcat(answer, "NOK : Poisson inexistant\n");
    return;
}

void cmd__get_fishes_continuously(aquarium *aq, client *c, char *answer)
{
    if (c != NULL)
    {
        c->sendFishes = 1;
    }
}

void cmd__log(aquarium *aq, client *c, char *answer)
{
    if (client__is_connected(c))
    {
        client__disconnect(c);
    }
    strcat(answer, "bye\n");
}

void cmd__undefined(aquarium *aq, client *c, char *answer)
{
    strcat(answer, "NOK : Commande Introuvable\n");
}

char* get_time(){
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    return asctime(timeinfo);
}