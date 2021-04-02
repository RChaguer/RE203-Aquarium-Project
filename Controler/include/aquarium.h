#ifndef __AQUARIUM_H__
#define __AQUARIUM_H__

#include <stdlib.h>
#include "list.h"
#include "dim_coord.h"
#include "view.h"

typedef struct aquarium {
    dim dim;
    list views;
} aquarium;

aquarium *  aquarium__initialize    (int width, int length);

int         aquarium__load          (aquarium *aq, char *filename);
int         aquarium__save          (aquarium *aq, char *filename);

int         aquarium__add_view      (aquarium *aq, view *v);
int         aquarium__delete_view   (aquarium *aq, int id);

char *      aquarium__status    (aquarium *aq);

void        aquarium__free          (aquarium *aq);

#endif /* __AQUARIUM_H__ */