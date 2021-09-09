#include "prompt.h"
#include "aquarium.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int cmd__parser(aquarium *aq, char *entry_cmd) {
    char command[strlen(entry_cmd)];
    strcpy(command, entry_cmd);

    // Utility Commands
    if (!strcmp(command, "exit\n"))
        return EXIT;
    if (!strcmp(command, "help\n") || !strcmp(command, "usage\n")) {
        cmd__usage();
        return USAGE;
    }

    // Managing the AQUARIUM Commands
    cmd ret = ERROR;
    char * token;
    token = strtok(command, " ");
    if (token != NULL) {
        if (!strcmp(token, "load"))
            ret = cmd__load(aq);
        else if (!strcmp(token, "show"))
            ret = cmd__show(aq);
        else if (!strcmp(token, "add"))
            ret = cmd__add(aq);
        else if (!strcmp(token, "del"))
            ret = cmd__delete(aq);
        else if (!strcmp(token, "save"))
            ret = cmd__save(aq);
    }
    if (ret == ERROR)
        cmd__error(entry_cmd);
    return ret;
}

int cmd__load(aquarium *aq){
    char * file = strtok(NULL, "\n");
    int ret = 0;
    if (file != NULL)
        ret = aquarium__load(aq, file);

    if (ret) {
        fprintf(stdout, "\t-> Aquarium loaded succesfully from file %s\n", file);
        return 1;
    } 
    fprintf(stderr, "\t-> wrong or non-existent file given for load command\n");
    cmd__usage();
    return 0;
}

int cmd__show(aquarium *aq){
    char *token = strtok(NULL, "\n");
    if (token != NULL) {
        if (!strcmp(token, "aquarium")) {
            char *status = aquarium__status(aq);
            fprintf(stdout, "\t-> Aquarium Status : \n%s", status);
            return 1;
        }
    } 
    fprintf(stderr, "\t-> Please Specify a valid argumnet for show command\n");
    cmd__usage();
    return 0;
}

int cmd__add(aquarium *aq) {
    char * type = strtok(NULL, " ");
    int ret = 0;
    if(type != NULL) {
        if (!strcmp(type, "view")) {
            char *id, *x, *y, *width, *height;
            id = strtok(NULL, " N");
            x = strtok(NULL, "x");
            y = strtok(NULL, "+");
            width = strtok(NULL, "+");
            height = strtok(NULL, "+");
            type = strtok(NULL, "\n");
            if (id != NULL && x != NULL && y != NULL && width != NULL && height != NULL) {
                if (atoi(id) != -1 && atoi(x) != -1 && atoi(y) != -1 && atoi(width) != -1 && atoi(height) != -1) {
                    view *v = view__initialize(atoi(id), atoi(x), atoi(y), atoi(height), atoi(width));
                    ret = aquarium__add_view(aq, v);
                    view__free(v);
                }
            }
            if (ret) {
                fprintf(stdout, "\t-> View N%s Added Succesfully\n", id);
                return 1;
            }
        }
    }
    fprintf(stderr, "\t-> Please Specify a valid argumnet for add command\n");
    cmd__usage();
    return 0;
}

int cmd__delete(aquarium *aq) {
    char * type = strtok(NULL, " ");
    int ret = 0;
    if(type != NULL) {
        if (!strcmp(type, "view")) {
            char *id;
            id = strtok(NULL, " N");
            type = strtok(NULL, "\n");
            if (id != NULL) {
                if (atoi(id) != -1) {
                    ret = aquarium__delete_view(aq, atoi(id));
                }
            }
            if (ret) {
                fprintf(stdout, "\t-> View N%d deleted Succesfully \n", atoi(id));
                return 1;
            }
        }
    }
    fprintf(stderr, "\t-> Please Specify a valid argument for delete command\n");
    cmd__usage();
    return 0;
}

int cmd__save(aquarium *aq){
    char * file = strtok(NULL, "\n");
    int ret = 0;
    if (file != NULL)
        ret = aquarium__save(aq, file);

    if (ret) {
        fprintf(stdout, "\t-> Aquarium saved succesfully from file %s\n", file);
        return 1;
    } 
    fprintf(stderr, "\t-> wrong or non-existent file given for save command\n");
    cmd__usage();
    return 0;
}

int cmd__exit(aquarium *aq) {
    return EXIT_SUCCESS;
}

int cmd__error(char *command) {
    fprintf(stderr, "\t->Uncompatible Command : \"%s\"\n", command);
    return 1;
}

int cmd__usage() {
    fprintf(stdout, "\t->This is a usage menu :\n    \
                     \t  load xxxx : load the aquarium xxxx\n   \
                     \t  show xxxx : show the aquarium xxxx\n   \
                     \t  save xxxx : save the aquarium xxxx\n   \
                     \t  add view Nz XxY+BundleX+BundleY : add the view z of size (width = BundleX, height = BundleY) at the coordinates (X,Y)\n   \
                     \t  del view Nz : delete the view z\n");
    return 1;
}