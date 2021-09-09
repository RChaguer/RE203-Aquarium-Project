#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "aquarium.h"
#include "aquarium_parser.h"
#include "mobility.h"
#include <string.h>
#include <stdlib.h>


aquarium *aquarium__new() {
    return aquarium__initialize(0, 0);
}

aquarium *aquarium__initialize(int width, int height) {
    aquarium *aq = (aquarium *) malloc(sizeof(aquarium));
    aq->loaded = 0;
    aq->dim.width = width;
    aq->dim.height = height;
    aq->views = list__init(view__copy, view__compare, view__free);
    aq->fishes = list__init(fish__copy, fish__compare, fish__free);
    return aq;
}

int aquarium__is_loaded(aquarium *aq) {
    return aq->loaded;
}

void aquarium__update(aquarium *aq, int width, int height) {
    aq->dim.width = width;
    aq->dim.height = height;
}

int aquarium__load(aquarium *aq, char *filename) {
    int ret = aquarium__load_from_file(aq, filename);
    if (ret) {
        aq->loaded = 1;
    }
    return ret;
}

int aquarium__save(aquarium *aq, char *filename) {
    FILE * fptr = fopen(filename,"w");

    if(fptr == NULL)
    {
        return 0;            
    }
    char* status = aquarium__status(aq);
   fprintf(fptr,"%s\n",status);
   fclose(fptr);
   return 1;
}

int aquarium__add_view(aquarium *aq, view *v) {
    if (list__find(aq->views, v) != NULL)
        return 0;
    list__add(aq->views, v);
    return 1;
}


int aquarium__add_fish(aquarium *aq, fish *f) {
    if (list__find(aq->fishes, f) != NULL)
        return 0;
    list__add(aq->fishes, f);
    return 1;
}

fish* aquarium__find_fish(aquarium *aq, char *id) {
    fish *tmp_f = fish__fake_initialize(id);

    fish *found_f = list__find(aq->fishes, tmp_f);

    if (!found_f) {
        free(tmp_f);
        return NULL;
    }

    free(tmp_f);
    return found_f;
}

int aquarium__delete_fish(aquarium *aq, char *id) {
    fish *tmp_f = fish__fake_initialize(id);
    if (!list__find(aq->fishes, tmp_f)) {
        free(tmp_f);
        return 0;
    }
    list__remove(aq->fishes, tmp_f);
    free(tmp_f);
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


view* aquarium__get__free_view(const aquarium *aq, int id) {
    if ( id == -1 ) {
        int i = 0;
        for (i = 0; i < list__size(aq->views); i++) {
            if ( !view__is_assigned((view *)list__get_from(aq->views, i))) {
                return (view *)list__get_from(aq->views, i);
            }
        }
        return NULL;
    }
    view *tmp = view__initialize(id, 0, 0, 0, 0);
    view *v = (view *)list__find(aq->views, tmp);
    view__free(tmp);
    if (v != NULL && !view__is_assigned(v)  ) {
        return v;
    }
    return NULL;
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

void aquarium__refresh(aquarium *aq, int rate) {
    if (aq != NULL) {
        fish *f;
        size_t size = list__size(aq->fishes);
        for (size_t i =0; i <size; i++) {
            f = (fish *) list__get_address_from(aq->fishes, i);
            fish__update(f, rate);
        }
    }
}

void aquarium__free(aquarium *aq) {
    list__clear(aq->views);
    list__clear(aq->fishes);
    free(aq);
}
