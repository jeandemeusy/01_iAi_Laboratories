#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define log_info(fmt, args...) fprintf(stdout, "\033[0;33m" fmt "\033[0m\n", ##args)
#define log_err(fmt, args...) fprintf(stderr, "\033[0;31m" fmt "\033[0m\n", ##args)

#endif //LOG_H
