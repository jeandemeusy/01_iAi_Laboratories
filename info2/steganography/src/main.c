#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "steganography.h"

#define MAX_CODE_LEN 1000

struct Options {
    bool encode;
    bool decode;
    char *input_filename;
    char *output_filename;
};

/**
 * Read command line arguments into the Option structure.
 * @param argc Number of arguments
 * @param argv Values of arguments
 * @return Options parsed.
 */
struct Options read_arguments(int argc, char *argv[])
{
    struct Options options = {0};

    while (1) {
        static struct option long_options[] = {{"encode", no_argument, 0, 'e'},
                                               {"decode", no_argument, 0, 'd'},
                                               {0, 0, 0, 0}};

        int option_index = 0;  // getopt_long stores the option index here.
        int c = getopt_long(argc, argv, "ed", long_options, &option_index);

        // Detect the end of the options.
        if (c == -1) break;

        switch (c) {
            case 'd':
                options.decode = true;
                break;

            case 'e':
                options.encode = true;
                break;

            case '?':
                // Ignore unknown options
                break;

            default:
                fprintf(stderr, "Unkown error!\n");
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Error: no input filename provided!\n");
        exit(EXIT_FAILURE);
    }
    options.input_filename = argv[optind++];

    if (options.encode) {
        if (optind < argc) {
            options.output_filename = argv[optind];
        }        
    }

    return options;
}

/**
 * Slurp a file into a dynamically allocated buffer.
 * Read `fp` until EOF found, store it into a char* buffer.
 * 
 * /!\ Do not forget to free the returned pointer after use.
 * 
 * @param fp Input file pointer
 * @return Buffer that contains the content of fp
 */
static char *fslurp(FILE *fp)
{
    size_t capacity = 4096;
    size_t len = 0;
    char *buffer = malloc(capacity * sizeof(char));

    // Read char by char, break if EOF reached
    int c;
    while ((c = fgetc(fp)) && !feof(fp)) {
        buffer[len] = c;
        if (++len == capacity)
            buffer = realloc(buffer, (capacity *= 2) * sizeof(char));
    }

    // Trim off buffer
    buffer = realloc(buffer, (len + 1) * sizeof(char));
    buffer[len] = '\0';

    return buffer;
}

int main(int argc, char *argv[])
{
    struct Options opt = read_arguments(argc, argv);
    char message[MAX_CODE_LEN] = { 0 };
    BMP *bmp = load_bmp(opt.input_filename);

    if (!bmp)
        return 1;

    if (opt.encode) {
        encode(bmp, fslurp(stdin));
        if (opt.output_filename)
            save_bmp(bmp, opt.output_filename);
        else
            fwrite_bmp(bmp,stdout);
    }

    if (opt.decode) {
        decode(bmp,message,MAX_CODE_LEN);
        
        if (opt.output_filename)
            fprintf(stdout,message);
        else
            fprintf(stderr,message);
    }
    
    free(bmp);
}
