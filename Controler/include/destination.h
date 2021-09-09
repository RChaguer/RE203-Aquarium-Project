#ifndef __DESTINATION_H__
#define __DESTINATION_H__

#include "dim_coord.h"

typedef struct {
    coord_float position;
    int period;
    dim bundle;
} destination;


destination *   destination__init       (coord_float position, int period, dim b);

char *          destination__to_char    (destination *d);

void            destination__free       (void *d);

void *          destination__copy       (const void *a);

int             destination__compare    (const void *a1, const void *a2);

#endif /* __DESTINATION_H__ */