#include "aquarium.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    
    aquarium *aq = aquarium__new();
    aquarium__load(aq, "./tst/aquarium.txt");
    char *status = aquarium__status(aq);
    printf("%s\n",status);
    free(status);
    printf("should display\n1000x1000\nN1 0x0+500+500\nN2 500x0+500+500\nN3 0x500+500+500\nN4 500x500+500+500\n");
    aquarium__free(aq); 
}
