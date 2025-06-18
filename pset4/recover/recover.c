#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define CHUNK 512

int main(int argc, char *argv[])
{
    // 2 arguments for CLA
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        return 1;
    }

    // filename formatting
    int jpeg_count = 0;
    char filename[10];

    uint8_t buffer[CHUNK]; // buffer
    FILE *img = NULL;

    // while there's still data left to rea
    while (fread(buffer, 1, CHUNK, card) == CHUNK)
    { // reading 512 bytes into a buffer
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        { // if JPEG header found
            // if img contains something, close img first
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", jpeg_count);
            img = fopen(filename, "w");
            jpeg_count++;
        }

        if (img != NULL)
        {
            fwrite(buffer, 1, CHUNK, img);
        }
    }
    fclose(img);
    fclose(card);
}
