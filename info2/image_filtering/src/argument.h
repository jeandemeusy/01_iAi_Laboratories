#ifndef ARGUMENT_H
#define ARGUMENT_H
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include "log.h"

typedef enum {
    NO_OPERATION,
    EDGE,
    V_EDGE,
    H_EDGE,
    SHARPEN,
    BLUR,
    RESIZE,
} operation;

typedef struct {
    bool adjust;
	operation type;
    size_t filter_size;
    char* resize;
    char *input_filename;
    char *output_filename;
} option_type;

option_type read_arguments(int argc, char *argv[]);
void usage(char* app_name);

#endif //ARGUMENT_H