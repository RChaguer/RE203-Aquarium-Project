#ifndef __AQUARIUM_PARSER_H__
#define __AQUARIUM_PARSER_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "aquarium.h"


dim         save__aquarium_dimention    (char *dimentions_line);

view    *   save__view                  (char *view_str);

int         aquarium__load_from_file    (aquarium *aq, char *file);

#endif /* __AQUARIUM_PARSER_H__ */