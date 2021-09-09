#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "aquarium.h"
#include "mobility.h"
#include "client.h"

char* get_time();
int protocol__parser(aquarium *aq, client *c, char* msg, char *answer);
void cmd__greeting(aquarium *aq, client *c, char *msg, char *answer);
void cmd__ping(aquarium *aq, client *c, char *msg, char *answer);
void cmd__get_fishes(aquarium *aq, client *c, char *answer);
void cmd__get_fishes_continuously(aquarium *aq, client *c, char *answer);
void cmd__addFish(aquarium *aq, client *c, char *msg, char *answer);
void cmd__delFish(aquarium *aq, client *c, char *msg, char *answer) ;
void cmd__startFish(aquarium *aq, client *c, char *msg, char *answer);
void cmd__log(aquarium *aq, client *c, char *answer);
void cmd__undefined(aquarium *aq, client *c, char *answer);

#endif