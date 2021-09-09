#ifndef _MOBILITY_H_
#define _MOBILITY_H_

#include "dim_coord.h"
#include "list.h"
#include "destination.h"
#include "view.h"

typedef enum
{
    Error=-1,
    DontMove,
    RandomWayPoint, 
    Horizontal, 
    Vertical
} mobility_type;

typedef enum
{
    Left,
    Right, 
    Up, 
    Down
} direction;

typedef struct
{
    coord_float curr_position;
    destination *destination;
    dim bundle;
    dim aq_resolution;
    mobility_type t;
    direction direction;
} mobility;

mobility *mobility__init(mobility_type t, coord_float pos, dim aq_res, dim b, direction d);

int mobility__generate(mobility *m, int period, int n);

int mobility__get_random(int range);

int mobility__get_period(coord_float p1, coord_float p2, dim aq_res);

int mobility__calculate(mobility *m, int period);

list mobility__get_destinations(mobility *m);

void mobility__refresh(mobility *m, int rate);

position mobility__check_pos_view(view *v, coord_float pos, dim b);

void mobility__free(mobility *m);

mobility_type set__mobility__type(char *mobility_char);

#endif /* _MOBILITY_H_ */