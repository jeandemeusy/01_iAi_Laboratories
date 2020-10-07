#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include "bmp.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void encode(BMP *bmp, char* message);
int decode(BMP *bmp, char* message, size_t size);


#endif // STEGANOGRAPHY_H