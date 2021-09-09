#ifndef _VIEW_H_
#define _VIEW_H_

#include "dim_coord.h"

typedef enum view_state
{
    ASSIGNED,
    NOT_ASSIGNED
} view_state;

typedef struct _view
{
    int id;
    coord_int c;
    view_state assigned;
    dim d;
} view;

view *view__initialize(int id, int x, int y, int height, int width);

int view__get_id(const view *v);
coord_int view__get_coord(const view *v);
dim view__get_dim(const view *v);

view *view__init_from_string(char *s);

char *view__status(const view *v);

int view__assign(view *v);
int view__disallow(view *v);
int view__is_assigned(view *v);

void *view__copy(const void *v);
int view__compare(const void *v1, const void *v2);
void view__free(void *v);

coord_float view__get_global_coord(view *v, coord_float *c);

coord_float view__get_local_coord(view *v, coord_float *c);

#endif /* _VIEW_H_ */