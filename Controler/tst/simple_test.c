#include "aquarium.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    aquarium *aq = aquarium__initialize(1000, 1000);
    view *v1 = view__initialize(1, 0, 0, 100, 100);
    view *v2 = view__initialize(2, 100, 100, 200, 200);
    view *v3 = view__initialize(3, 200, 200, 300, 300);
    int ret;
    ret = aquarium__add_view(aq, v1);
    printf("ret1 %d (should be 1)\n", ret);
    ret = aquarium__add_view(aq, v2);
    printf("ret2 %d (should be 1)\n", ret);
    ret = aquarium__add_view(aq, v3);
    printf("ret3 %d (should be 1)\n", ret);

    ret = aquarium__delete_view(aq, 2);
    printf("ret4 %d (should be 1)\n", ret);
    ret = aquarium__delete_view(aq, 2);
    printf("ret5 %d (should be 0)\n", ret);
    char *view_st = view__status(v1);
    //printf("ret6 %d (should be 1)\n", ret);
    printf("%s\n", view_st);
    char *aq_st = aquarium__status(aq);
    printf("%s", aq_st);
    aquarium__free(aq);
    view__free(v1);
    view__free(v2);
    view__free(v3);
    free(view_st);
    free(aq_st);
}
