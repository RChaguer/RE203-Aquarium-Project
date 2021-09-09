#ifndef __FISH_H__
#define __FISH_H__

#include "dim_coord.h"
#include "mobility.h"
#include "view.h"

typedef enum
{
    notStarted,
    started,
} state;

typedef struct fish
{
    char *id;
    dim bundle;
    dim aq_res;
    coord_float position;
    mobility *mobility;
    state state;
} fish;

fish *fish__initialize(char *id, int bundle_width, int bundle_height, float x, float y, mobility_type mobility, dim aq_res);

fish *fish__fake_initialize(char *id);

void fish__start(fish *f);

void *fish__copy(const void *f);

int fish__compare(const void *f1, const void *f2);

void fish__get_view_destination(view *v, fish *f, char *msg);

int fish__update(fish *f, int rate);

void fish__free(void *f);

#endif /* __FISH_H__ */