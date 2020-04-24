#pragma once

#include <stdint.h>
#include <stdio.h>

#pragma pack(push, 1)
typedef struct BMPFileHeader {
    uint16_t type;  // Must be 'BM' 0x4d42
    uint32_t size;  // Size of the whole file 
    uint16_t reserved1;  // Reserved: must be 0
    uint16_t reserved2;  // Reserved: must be 0
    uint32_t offset_bytes;  // Offset to the beginning of the image
} BMPFileHeader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct BMPInfoHeader {
    uint32_t header_size;  // Always 40 for a HEADER V5
    int32_t width;  // Image width in pixels
    int32_t height;  // Image height in pixels
    uint16_t planes; // Number of color planes, must be 1
    uint16_t bit_per_pixels; // Number of bits per pixel, usually 24 for a color image
    uint32_t compression;// Type of compression
    uint32_t image_size;  // Size of image in bytes
    int32_t x_pixels_per_meter;  // Number of pixels per meter in x axis
    int32_t y_pixels_per_meter;  // Number of pixels per meter in y axis
    uint32_t colors_used;  // Number of colors used by color map
    uint32_t important_colors;  // Number of colors that are important
} BMPInfoHeader;
#pragma pack(pop)

typedef struct BMP {
    BMPFileHeader header;
    BMPInfoHeader info;
    uint8_t data[];
} BMP;

typedef struct Pixel24Bits { 
    uint8_t blue :8; 
    uint8_t green :8; 
    uint8_t red :8; 
} Pixel24Bits;

BMP* load_bmp(char *filename);
void save_bmp(BMP *bmp, char* filename);
void fwrite_bmp(BMP *bmp, FILE* fp);
void free_bmp(BMP *bmp);
