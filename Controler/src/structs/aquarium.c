#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "aquarium.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


aquarium *aquarium__initialize(int width, int height) {
    aquarium *aq = (aquarium *) malloc(sizeof(aquarium));
    aq->dim.width = width;
    aq->dim.height = height;
    aq->views = list__init(view__copy, view__compare, view__free);
    return aq;
}

aquarium *aquarium__new() {
    return aquarium__initialize(0, 0);
}

void aquarium__update(aquarium *aq, int width, int height) {
    aq->dim.width = width;
    aq->dim.height = height;
}

int aquarium__load(aquarium *aq, char *filename) {
    (void *) aq;
    (void *) filename;
    return 1;
}

int aquarium__save(aquarium *aq, char *filename);

int aquarium__add_view(aquarium *aq, view *v) {
    if (list__find(aq->views, v) != NULL)
        return 0;
    list__add(aq->views, v);
    return 1;
}

int aquarium__delete_view(aquarium *aq, int id) {
    view *tmp_v = view__initialize(id, 0, 0, 0, 0);
    if (!list__find(aq->views, tmp_v)) {
        view__free(tmp_v);
        return 0;
    } 
    list__remove(aq->views, tmp_v);
    if (list__find(aq->views, tmp_v)) {
        view__free(tmp_v);
        return -1;
    }
    view__free(tmp_v);
    return 1;
}

char *aquarium__status(aquarium *aq) {
    char* st = (char *) malloc(BUFFER_LENGTH);
    st[0]='\0';

    char* aq_st;
    asprintf(&aq_st, "%dx%d\n", aq->dim.width, aq->dim.height);
    strcat(st, aq_st);
    free(aq_st);

    char * view_st;
    view * v;
    size_t size = list__size(aq->views);
    for (size_t i =0; i <size; i++) {
        v = (view *) list__get_address_from(aq->views, i);
        view_st = view__status(v);
        strcat(st, view_st);
        free(view_st);
    }
    return st;
}

void aquarium__free(aquarium *aq) {
    list__clear(aq->views);
    free(aq);
}