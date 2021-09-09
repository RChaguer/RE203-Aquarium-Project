#include "mobility.h"
#include "dim_coord.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define NB_STEPS 100

void display__destination(FILE *f, mobility *m) {
    fprintf(f, "\tdestination (x, y)= (%lf, %lf)\n", m->destination->position.x, m->destination->position.y);
}

int main() {
    FILE *f = fopen("./tst/mobility_test_log.txt", "w");
    if ( f == NULL) {
        printf("Can't open log file\n");
        return EXIT_FAILURE;
    }
    fprintf(f, "get__random(10) = %d (value should be < 10) \n", mobility__get_random(10));
    dim aq_res;
    coord_float initial_pos;
    dim bundle;
    int rate = 5;
    aq_res.width = 1000;
    aq_res.height = 1000;
    initial_pos.x = 0.0;
    initial_pos.y = 0.0;
    bundle.height = 3;
    bundle.width = 4;
    
    fprintf(f, "\n\t___________ RandomWayPoint mobility test _____________\n");
    mobility *m = mobility__init(RandomWayPoint, initial_pos, aq_res, bundle, Right);
    
    fprintf(f, "Step 0 :\n");
    display__destination(f, m);
    fprintf(f, "\tperiod is %d\n", m->destination->period);
    
    int i;
    for (i = 1; i < NB_STEPS; i++) {
        fprintf(f, "Step %d :\n", i);
        mobility__refresh(m, rate);
        display__destination(f, m);
        fprintf(f, "\tperiod is %d\n", m->destination->period);
    }
    
    mobility__free(m);


    fprintf(f, "\n\t___________ Horizontal mobility test _____________\n");
    m = mobility__init(Horizontal, initial_pos, aq_res, bundle, Right);
    
    fprintf(f, "Step 0 :\n");
    display__destination(f, m);
    fprintf(f, "\tperiod is %d\n", m->destination->period);
    
    for (i = 1; i < NB_STEPS; i++) {
        fprintf(f, "Step %d :\n", i);
        mobility__refresh(m, rate);
        display__destination(f, m);
        fprintf(f, "\tperiod is %d\n", m->destination->period);
    }
    
    mobility__free(m);
    
    
    fprintf(f, "\n\t___________ Vertical mobility test _____________\n");
    m = mobility__init(Vertical, initial_pos, aq_res, bundle, Right);
    
    fprintf(f, "Step 0 :\n");
    display__destination(f, m);
    fprintf(f, "\tperiod is %d\n", m->destination->period);
    
    for (i = 1; i < NB_STEPS; i++) {
        fprintf(f, "Step %d :\n", i);
        mobility__refresh(m, rate);
        display__destination(f, m);
        fprintf(f, "\tperiod is %d\n", m->destination->period);
    }
    mobility__free(m);

    fclose(f);
    return EXIT_SUCCESS;
}