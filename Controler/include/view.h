#ifndef _VIEW_H_
#define _VIEW_H_


#define BUFFER_LENGTH 128
#include "dim_coord.h"
#include <stdlib.h>

typedef struct _view {
    int id;
    coord_int c;
    dim d;
} view;

view *      view__initialize         (int id, int x, int y, int height, int width);

coord_int   view__get_coord          (const view *v);
dim         view__get_dim            (const view *v);

view *      view__init_from_string   (char *s, size_t *len);
char *      view__status             (const view *v);
void *      view__copy               (const void *v);
int         view__compare            (const void *v1, const void *v2);
void        view__free               (void *v);


#endif /* _VIEW_H_ */