#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "log.h"


typedef enum {
    HELP = 1,
    ALPHA,
    NATURAL,
    COUNT,
} action_type;

typedef struct {
    action_type action;
} option_type;

option_type read_arguments(int argc, char *argv[]);
int usage(char* app_name);

#endif //ARGUMENT_H