#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

static size_t filesize(FILE* fp) {
    size_t cursor = ftell(fp);
    fseek(fp, 0, SEEK_END);
    size_t filesize = ftell(fp);
    fseek(fp, cursor, SEEK_SET);    
    return filesize;
}

BMP* load_bmp(char *filename)
{
    BMP *bmp;

    // Read whole image
    size_t size;
    {
        FILE *fp;
        if ((fp = fopen(filename,"rb")) == NULL) return NULL;
        size = filesize(fp);
        if ((bmp = malloc(size)) == NULL) return NULL;    
        
        fread(bmp, size, 1, fp);
        fclose(fp);
    }
    
    if (bmp->header.type != 0x4d42) {free(bmp); return NULL;}
    if (bmp->header.size != size) {free(bmp); return NULL;}
    if (bmp->info.header_size != sizeof(bmp->info)) {free(bmp); return NULL;}

    return bmp;    
}

void free_bmp(BMP *bmp) {
    if (bmp == NULL) return;
    free(bmp);
}

void save_bmp(BMP *bmp, char* filename) {
    FILE *fp = fopen(filename, "wb");
    fwrite(bmp, bmp->header.size, 1, fp);
    fclose(fp);
}

void fwrite_bmp(BMP *bmp, FILE* fp) {
    fwrite(bmp, bmp->header.size, 1, fp);
}