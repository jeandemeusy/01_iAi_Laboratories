#ifndef TEXT_ORDERING_H
#define TEXT_ORDERING_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "argument.h"
#include "log.h"

#define NAME_MAX_SIZE 128

int comp_alpha(const void* str1, const void* str2);
int comp_num(const void* str1, const void* str2);

int sort_names(const uint32_t num_names, char* names[], action_type action);
void print_names(const uint32_t num_names, char* names[]);

#endif //TEXT_ORDERING_H
