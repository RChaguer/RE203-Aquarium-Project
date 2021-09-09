
#include "destination.h"
#include "list.h"
#include <stdlib.h>

destination *destination__init(coord_float position, int period, dim b) {
    destination *d = malloc(sizeof(destination));
    d->bundle = b;
    d->period = period;
    d->position = position;
    return d;
}

void destination__free(void *d) {
    free((destination *) d);
}

void * destination__copy(const void *a) {
    return copyAddress(a);
}

int destination__compare(const void *a1, const void *a2) {
    return compareAddress(a1, a2);
}