#include "steganography.h"

/**
 * Encode message into BMP using LSB of pixels as carrier.
 *
 * @param bmp BMP image loaded in memory
 * @param message String containing the message to encode
 */
 void encode(BMP *bmp, char* message) {
    if (bmp->info.image_size < 8*strlen(message) + 1) {
        fprintf(stderr, "Error: not enough space to store message\n");
        return;
    }
    
    uint8_t c;
    uint8_t *data = bmp->data;
    do {
        c = *message++;
        for (int i = 7; i >= 0; --i) {
            *data = (*data & ~0x1) | ((c >> i) & 0x1);
            data++;
        }
    } while (c != '\0');
 }

 /**
  * Decode an encoded message from a BMP using pixel's LSB
  * as carrier.
  *
  * @param bmp BMP image loaded in memory with embedded message
  * @param message Buffer to save the decoded message
  * @param size Maximum size of the destination message buffer
  * @return Effective size of the message '\0' included.
  */
  int decode(BMP *bmp, char* message, size_t size) {
    uint8_t *data = bmp->data;

    do {
        for (int i = 7; i >= 0; --i)
            *message |= (*data++ & 0x1) << i;
        message++;
    } while(data - bmp->data < size*8 && (*message-1) != '\0');
    return data - bmp->data - 1;
  }