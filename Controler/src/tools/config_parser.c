#include "config_parser.h"

int port = -1;
int timeout = -1;
int update = -1;

int parse_file(char *file) {
    char buffer[BUFFER_LINE_SIZE];

    FILE *inputFile = fopen(file, "r");
    if (inputFile == NULL) {
        printf("Cannot open file %s\n", file);
        return 0;
    }

    while (!feof(inputFile)) {
        fgets(buffer, BUFFER_LINE_SIZE, inputFile);
        char *p = strtok(buffer, " =");
        while (p != NULL) {
            if (*p == '#')
                break;

            if (strcmp("controller-port", p) == 0) {
                p = strtok(NULL, " =");
                if (p == NULL)
                    break;
                port = atoi(p);
                break;
            }

            if (strcmp("display-timeout-value", p) == 0) {
                p = strtok(NULL, " =");
                if (p == NULL)
                    break;
                timeout = atoi(p);
                break;
            }

            if (strcmp("fish-update-interval", p) == 0) {
                p = strtok(NULL, " =");
                if (p == NULL)
                    break;
                update = atoi(p);
                break;
            }
            p = strtok(NULL, " =");
        }
    }
    fclose(inputFile);
    return 1;
}

int get_port() {
    return port;
}

int get_timeout() {
    return timeout;
}

int get_update() {
    return update;
} 