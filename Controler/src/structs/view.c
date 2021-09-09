#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "view.h"
#include "fish.h"
#include "aquarium_parser.h"
#include <stdlib.h>
#include <stdio.h>

view *view__initialize(int id, int x, int y, int height, int width)
{
    view *v = (view *)malloc(sizeof(view));
    v->id = id;
    v->c.x = x;
    v->c.y = y;
    v->d.height = height;
    v->d.width = width;
    v->assigned = NOT_ASSIGNED;
    return v;
}

int view__get_id(const view *v)
{
    return v->id;
}

coord_int view__get_coord(const view *v)
{
    return v->c;
}

dim view__get_dim(const view *v)
{
    return v->d;
}

view *view__init_from_string(char *s)
{
    return save__view(s);
}

char *view__status(const view *v)
{
    char *s;
    int ret = asprintf(&s, "N%d %dx%d+%d+%d\n", v->id, v->c.x, v->c.y, v->d.width, v->d.height);
    if (ret != -1)
        return s;
    return NULL;
}

int view__is_assigned(view *v)
{
    if (v->assigned == ASSIGNED)
    {
        return 1;
    }
    return 0;
}

int view__assign(view *v)
{
    if (v == NULL || v->assigned == ASSIGNED)
    {
        return 0;
    }
    v->assigned = ASSIGNED;
    return 1;
}

int view__disallow(view *v)
{
    v->assigned = NOT_ASSIGNED;
    return 1;
}

void *view__copy(const void *v)
{
    view *_v = (view *)v;
    view *cp_v = view__initialize(_v->id, _v->c.x, _v->c.y, _v->d.height, _v->d.width);
    return cp_v;
}

int view__compare(const void *v1, const void *v2)
{
    view *_v1 = (view *)v1,
         *_v2 = (view *)v2;
    return _v1->id - _v2->id;
}

void view__free(void *v)
{
    free(v);
}

coord_float view__get_global_coord(view *v, coord_float *c)
{
    coord_float global_c = {c->x + v->c.x, c->y + v->c.y};
    return global_c;
}

coord_float view__get_local_coord(view *v, coord_float *c)
{
    coord_float local_c = {c->x - v->c.x, c->y - v->c.y};
    return local_c;
}