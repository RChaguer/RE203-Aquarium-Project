#include <aquarium_parser.h>
#include <list.h>

#define MAX_LINE_LENGTH 100
#define MAX_VIEWS 20


dim save__aquarium_dimention(char *dimentions_line) {
  dim dimentions;
  int w, h;
  char x[2] = "x";
  w = atoi(strtok(dimentions_line, x));
  h = atoi(strtok(NULL, x));
  dimentions.width = w;
  dimentions.height = h;
  return dimentions;
}

view *save__view(char *view_str) {
    
    //saving the id
    view *view;
    int id, x, y, height, width;
    char d[2] = " ";
    id = atoi(strtok(view_str+1, d));

    //Saving the coordinates str
    d[0] = '+';
    char *coordinates = strtok(NULL, d);
    
    //Saving the view dimentions
    view_str = strtok(NULL, d);
    width = atoi(view_str);
    d[0] = '\n';
    view_str = strtok(NULL, d);
    height = atoi(view_str);

    //Saving the coordinates
    d[0] = 'x';
    coordinates = strtok(coordinates, d);
    x = atoi(coordinates);
    coordinates = strtok(NULL, d);
    y = atoi(coordinates);
    view = view__initialize(id, x, y, height, width);
    return view;
}


int aquarium__load_from_file(aquarium *a, char *file) {
    FILE *aquarium = fopen(file, "r");
    if (aquarium != NULL) {
        char dimentions[MAX_LINE_LENGTH];
        if ( fgets(dimentions, MAX_LINE_LENGTH, aquarium) == NULL ) {
            fprintf(stderr, "Error");
        }
        dim dim = save__aquarium_dimention(dimentions);
        aquarium__update(a, dim.width, dim.height);
        char views_str[MAX_VIEWS][MAX_LINE_LENGTH];
        int views_number = 0;
        while ( fgets(views_str[views_number], MAX_LINE_LENGTH, aquarium) ) {
            views_number++;
        }
        view *v;
        for (int i = 0; i < views_number; i++ ) {
            v = save__view(views_str[i]);
            aquarium__add_view(a, v);
            view__free(v);
        }
        v = NULL;
        fclose(aquarium);
        return 1;
    }
    return 0;
}