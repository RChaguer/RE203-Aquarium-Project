#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fish.h"
#include "view.h"

fish *fish__initialize(char *id, int bundle_width, int bundle_height, float x, float y, mobility_type mobility, dim aq_res)
{
    fish *f = (fish *)malloc(sizeof(fish));
    f->id = id;
    f->bundle.width = bundle_width;
    f->bundle.height = bundle_height;
    f->position.x = x;
    f->position.y = y;
    f->mobility = mobility__init(mobility, f->position, aq_res, f->bundle, Right);
    f->state = notStarted;
    return f;
}

fish *fish__fake_initialize(char *id)
{
    fish *f = (fish *)malloc(sizeof(fish));
    f->id = id;
    return f;
}

void fish__start(fish *f)
{
    f->state = started;
}

void *fish__copy(const void *f)
{
    return (void *)f;
}

int fish__compare(const void *f1, const void *f2)
{
    fish *_f1 = (fish *)f1,
         *_f2 = (fish *)f2;
    return strcmp(_f1->id, _f2->id);
}

int fish__update(fish *f, int rate)
{
    if (f->state)
    {
        mobility__calculate(f->mobility, rate);
    }
    return 1;
}

void fish__free(void *f)
{
    free(((fish *)f)->id);
    mobility__free(((fish *)f)->mobility);
    free(f);
}

void fish__get_view_destination(view *v, fish *f, char *msg)
{
    position p_before = mobility__check_pos_view(v, (f->mobility)->curr_position, f->mobility->bundle);
    position p_after = mobility__check_pos_view(v, (f->mobility->destination)->position, f->mobility->bundle);

    if (!p_before && p_after)
    {
        char buffer_old[128];
        coord_float view_old_coord = view__get_local_coord(v, &((f->mobility)->curr_position));
        int perc_old_x = (view_old_coord.x / v->d.width) * 100;
        int perc_old_y = (view_old_coord.y / v->d.height) * 100;
        sprintf(buffer_old, "[%s at %dx%d,%dx%d,%d] ", f->id, perc_old_x, perc_old_y, f->bundle.width, f->bundle.height, 0);
        strcat(msg, buffer_old);
    }

    if (p_after || (p_before && !p_after))
    {
        char buffer[128];
        coord_float view_coord = view__get_local_coord(v, &(f->mobility->destination->position));
        int perc_x = (view_coord.x / v->d.width) * 100;
        int perc_y = (view_coord.y / v->d.height) * 100;
        sprintf(buffer, "[%s at %dx%d,%dx%d,%d] ", f->id, perc_x, perc_y, f->bundle.width, f->bundle.height, f->mobility->destination->period);
        strcat(msg, buffer);
    }
}