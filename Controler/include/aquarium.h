#ifndef __AQUARIUM_H__
#define __AQUARIUM_H__

#include <stdlib.h>
#include "list.h"
#include "dim_coord.h"
#include "view.h"
#include "fish.h"

#define BUFFER_LENGTH 500

typedef struct aquarium {
    int loaded;
    dim dim;
    list views;
    list fishes;
} aquarium;


aquarium  *  aquarium__new              ();

aquarium  *  aquarium__initialize       (int width, int height);

void         aquarium__update           (aquarium *aq, int width, int height);

int          aquarium__load             (aquarium *aquarium, char *filename);
int          aquarium__is_loaded        (aquarium *aq);


int         aquarium__save              (aquarium *aq, char *filename);

view*       aquarium__get__free_view    (const aquarium *aq, int id);
int         aquarium__add_view          (aquarium *aq, view *v);
int         aquarium__delete_view       (aquarium *aq, int id);

int         aquarium__add_fish          (aquarium *aq, fish *f);
int         aquarium__delete_fish       (aquarium *aq, char *id);
fish*       aquarium__find_fish         (aquarium *aq, char *id);

char *      aquarium__status            (aquarium *aq);
void        aquarium__refresh           (aquarium *aq, int rate);

void        aquarium__free              (aquarium *aq);

#endif /* __AQUARIUM_H__ */