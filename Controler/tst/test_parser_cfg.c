#include "config_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


int main() {
    int a = parse_file("./tst/controller.cfg");
    assert(a != 0);
    printf("Controller port is %d (should be 12345)\n", get_port());
    printf("timeout is %d (should be 45)\n", get_timeout());
    printf("update %d (should be 1)\n", get_update());
    return EXIT_SUCCESS;
}