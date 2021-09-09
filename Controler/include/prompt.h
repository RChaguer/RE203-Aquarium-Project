#ifndef _PROMPT_H_
#define _PROMPT_H_

#include "aquarium.h"

typedef enum {
    ERROR=0, LOAD, SHOW, ADD, DEL, SAVE, USAGE, EXIT
} cmd;

int cmd__parser(aquarium *aq, char *entry_cmd);

int cmd__load(aquarium *aq);
int cmd__show(aquarium *aq);
int cmd__add(aquarium *aq);
int cmd__delete(aquarium *aq);
int cmd__save(aquarium *aq);
int cmd__error(char *command);
int cmd__usage();
int cmd__exit();
void *terminal_handler(void* args);
#endif /* _PROMPT_H_ */
