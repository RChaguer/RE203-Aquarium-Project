#ifndef __CONFIG_PARSER_H__
#define __CONFIG_PARSER_H__

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FILE_NAME "controller.cfg"

#define BUFFER_LINE_SIZE 64



int     parse_file  (char *file);

int     get_port    ();

int     get_timeout ();

int     get_update  ();

#endif /* __CONFIG_PARSER_H__ */