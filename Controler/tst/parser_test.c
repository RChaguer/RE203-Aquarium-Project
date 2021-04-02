#include "prompt.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    char error_command[] = "wat";
    char usage_command[] = "usage";
    char add_command[] = "add view N5 400x400+400+200";
    char del_command[] = "del view N5";
    char exit_command[] = "exit";
    
    aquarium *aq = aquarium__initialize(1000, 1000);
    view *v1 = view__initialize(1, 0, 0, 100, 100);
    view *v2 = view__initialize(2, 100, 100, 200, 200);
    view *v3 = view__initialize(3, 200, 200, 300, 300);
    aquarium__add_view(aq, v1);
    aquarium__add_view(aq, v2);
    aquarium__add_view(aq, v3);



    int err = cmd__parser(aq, error_command);
    printf("err = ERROR : %d\n", err == ERROR);
    int us = cmd__parser(aq, usage_command);
    printf("us = USAGE : %d\n", us == USAGE);
    int add = cmd__parser(aq, add_command);
    printf("add = 1 : %d\n", add == 1);
    int del = cmd__parser(aq, del_command);
    printf("del = 1 : %d\n", del == 1);
    int exit = cmd__parser(aq, exit_command);
    printf("exit = EXIT : %d\n", exit == EXIT);


    aquarium__free(aq);
    view__free(v1);
    view__free(v2);
    view__free(v3);

    return EXIT_SUCCESS;
}