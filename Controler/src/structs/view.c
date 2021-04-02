#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

view *view__initialize(int id, int x, int y, int height, int width) {
    view *v = (view *) malloc(sizeof(view));
    v->id = id;
    v->c.x = x;
    v->c.y = y;
    v->d.height = height;
    v->d.width = width;
    return v;
}

int view__get_id(const view *v) {
    return v->id;
}

coord_int view__get_coord(const view *v) {
    return v->c;
}

dim view__get_dim(const view *v) {
    return v->d;
}

view *view__init_from_string(char *s, size_t *len);

char * view__status(const view *v) {
    char * s;
    int ret = asprintf(&s, "N%d %dx%d+%d+%d\n", v->id, v->c.x, v->c.y, v->d.width, v->d.height);
    if (ret != -1)
        return s;
    return NULL; 
}

void *view__copy(const void *v) {
    view *_v = (view *) v;
    view *cp_v = view__initialize(_v->id, _v->c.x, _v->c.y, _v->d.height, _v->d.width);
    return cp_v;
}

int view__compare(const void *v1, const void *v2) {
    view * _v1 = (view *) v1, 
         * _v2 = (view *) v2;

    return _v1->id - _v2->id;
}

void view__free(void *v) {
    free(v);
}
