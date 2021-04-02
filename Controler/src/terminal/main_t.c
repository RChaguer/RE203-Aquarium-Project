#include "prompt.h"
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    const char *prompt = "$ ";
    char * line;

    aquarium *aq = aquarium__initialize(1000, 1000);

    while (1) {
        //read line from terminal
        line = readline(prompt);
        //And then we analyze it
        if (cmd__parser(aq, line) == EXIT) {
            break;
        }
        free(line);
    }

    aquarium__free(aq);
    return EXIT_SUCCESS;
}