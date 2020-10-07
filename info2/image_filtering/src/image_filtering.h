#ifndef IMAGE_FILTERING_H
#define IMAGE_FILTERING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argument.h"
#include "log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image/stb_image_write.h"

#define MAX(X,Y) (X)>(Y) ? (X):(Y)
#define MIN(X,Y) (X)<(Y) ? (X):(Y)
#define SQRT(X,Y) sqrt((X)*(X) + (Y)*(Y))

// 2d operations
void conv_2d(uint8_t* src, uint8_t* dst, size_t src_w, size_t src_h, float* f, size_t h_w);
void get_filter_kernel(float** f, size_t f_w, operation type);
uint8_t* edge(uint8_t* src, size_t src_w, size_t src_h);
void adjust_constrast(uint8_t* src, size_t src_w, size_t src_h);
void resize(uint8_t** src, int* src_w, int* src_h, char* arg);

// wrapper
uint8_t* filter(uint8_t* src, size_t src_w, size_t src_h, operation type, size_t size);
uint8_t* imread(char* filename, int* width, int* height);
void imsave(uint8_t* img, char* filename, int width, int height);

// Setter-getter
uint8_t get_pixel_uint8(uint8_t* img, size_t width, size_t x, size_t y);
float get_pixel_float(float* img, size_t width, size_t x, size_t y);
void set_pixel(uint8_t* img, size_t width, size_t x, size_t y, uint8_t val);
uint8_t get_min(uint8_t* src, size_t src_w, size_t src_h);
uint8_t get_max(uint8_t* src, size_t src_w, size_t src_h);

#endif //IMAGE_FILTERING_H