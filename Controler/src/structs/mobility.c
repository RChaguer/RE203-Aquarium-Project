#include <string.h>
#include "mobility.h"
#include "destination.h"
#include "view.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NB_MOB_TYPES 4

static char *mobilities[NB_MOB_TYPES] = {"DontMove",
                              "RandomWayPoint", "Horizontal", "Vertical"};

mobility *mobility__init(mobility_type t, coord_float pos, dim aq_res, dim b, direction d)
{
    mobility *m = (mobility *)malloc(sizeof(mobility));
    m->t = t;
    m->curr_position = pos;
    m->bundle = b;
    m->aq_resolution = aq_res;
    m->destination = destination__init(pos, 0, m->bundle);
    m->direction = Right;
    return m;
}

int mobility__get_random(int range) {
    static int first_rand = 1;
    if ( first_rand != 0 ) {
        srand(time(NULL));
        first_rand = 0;
    }
    return (rand() % (range + range + 1)) - range;
}

int mobility__get_period(coord_float p1, coord_float p2, dim aq_res) {
    double dist;
    double aq_dim;
    dist = fabs(p1.x - p2.x) + fabs(p1.y - p2.y);
    aq_dim = aq_res.width + aq_res.height;
    return (dist*100) / aq_dim;
}

int mobility__calculate(mobility *m, int period)
{
    coord_float new_pos;
    switch (m->t)
    {
    case DontMove:
        new_pos.x = m->curr_position.x;
        new_pos.y = m->curr_position.y;
        m->curr_position.x = m->destination->position.x;
        m->curr_position.y = m->destination->position.y;
        m->destination->position.x = new_pos.x;
        m->destination->position.y = new_pos.y;
        break;
    case Horizontal:
        m->curr_position.x = m->destination->position.x;
        m->curr_position.y = m->destination->position.y;
        if (m->direction == Right) {
            new_pos.x = m->curr_position.x + (m->aq_resolution.width*period)/50;
            if ( new_pos.x + m->bundle.width > m->aq_resolution.width) {
                m->destination->position.x = m->curr_position.x - (m->aq_resolution.width*period)/50;
                m->direction = Left;
            }
            else {
                m->destination->position.x = new_pos.x;
            }
        }
        else {
            new_pos.x = m->curr_position.x - (m->aq_resolution.width*period)/50;
            if ( new_pos.x < 0 ) {
                m->destination->position.x = m->curr_position.x + (m->aq_resolution.width*period)/50;
                m->direction = Right;
            }
            else {
                m->destination->position.x = new_pos.x;
            }
        }
        break;
    case RandomWayPoint:
        m->curr_position.x = m->destination->position.x;
        m->curr_position.y = m->destination->position.y;
        
        double rand_x = mobility__get_random((m->aq_resolution.width*period)/30);
        double rand_y = mobility__get_random((m->aq_resolution.height*period)/30);
        new_pos.x = m->curr_position.x + rand_x;
        new_pos.y = m->curr_position.y + rand_y;
        if (m->direction == Right) {
            if ( new_pos.x + m->bundle.width > m->aq_resolution.width) {
                m->destination->position.x = m->curr_position.x - rand_x;
                m->direction = Left;
            } else if ( new_pos.x < 0 ) {
                m->destination->position.x = m->curr_position.x - rand_x;
                m->direction = Right;
            }
            else {
                m->destination->position.x = new_pos.x;
            }
        }
        else {
            if ( new_pos.x < 0 ) {
                m->destination->position.x = m->curr_position.x - rand_x;
                m->direction = Right;
            } else if ( new_pos.x + 3*m->bundle.width > m->aq_resolution.width) {
                m->destination->position.x = m->curr_position.x - rand_x;
                m->direction = Left;
            } 
            else {
                m->destination->position.x = new_pos.x;
            }
        }
        if ( new_pos.y > m->aq_resolution.height ) {
            m->destination->position.y = m->curr_position.y - rand_y;
        }
        else if ( new_pos.y - 3*m->bundle.height < 0 ) {
            m->destination->position.y = m->curr_position.y - rand_y;
        } 
        else {
            m->destination->position.y = new_pos.y;
        }
        break;

    case Vertical:
        m->curr_position.x = m->destination->position.x;
        m->curr_position.y = m->destination->position.y;
        if (m->direction == Up) {
            new_pos.y = m->curr_position.y + (m->aq_resolution.height*period)/50;
            if ( new_pos.y > m->aq_resolution.height) {
                m->destination->position.y = m->curr_position.y - (m->aq_resolution.height*period)/50;
                m->direction = Down;
            }
            else {
                m->destination->position.y = new_pos.y;
            }
        }
        else {
            new_pos.y = m->curr_position.y - (m->aq_resolution.height*period)/50;
            if ( new_pos.y - m->bundle.height < 0 ) {
                m->destination->position.y = m->curr_position.y + (m->aq_resolution.width*period)/50;
                m->direction = Up;
            }
            else {
                m->destination->position.y = new_pos.y;
            }
        }
    break;
    default:
        break;
    }
    m->destination->period = period;
    return 1;
}

position mobility__check_pos_view(view *v, coord_float pos, dim b)
{
    if (v->c.x <= pos.x + b.width && v->c.y <= pos.y + b.height &&
        v->c.x + v->d.width >= pos.x && v->c.y + v->d.height >= pos.y)
        return IN;
    return OUT;
}

void mobility__refresh(mobility *m, int rate) {
    mobility__calculate(m, rate);
}

void mobility__free(mobility *m)
{
    destination__free(m->destination);
    free(m);
}

mobility_type set__mobility__type(char *mobility_char)
{
    mobility_type m;
    for (int i = 0; i < NB_MOB_TYPES; i++)
    {
        switch (strcmp(mobility_char, mobilities[i]))
        {
        case 0:
            m = i;
            return m;
        default:
            break;
        }
    }
    return Error;
}