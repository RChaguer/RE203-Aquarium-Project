#ifndef _DIM_COORD_H_
#define _DIM_COORD_H_

typedef enum  {
    OUT = 0,
    IN
} position;

typedef struct _dimension {
    int width;
    int height;
} dim;

typedef struct _coordinate_int {
    int x;
    int y;
} coord_int;

typedef struct _coordinate_float {
    double x;
    double y;
} coord_float;

#endif /* _DIM_COORD_H_ */