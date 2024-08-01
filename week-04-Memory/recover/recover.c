#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    int open = 0;
    char jpg_name[8];
    int file_count = 0;
    FILE *output = NULL;

    // While there's still data left to read from the memory card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // Create JPEGs from the data
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // This is the start of a new JPEG
            if (open == 1)
            {
                // if file is open for the first time
                fclose(output);
                file_count++;
            }
            sprintf(jpg_name, "%03d.jpg", file_count);
            output = fopen(jpg_name, "w");
            if (output == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            open = 1;
        }
        // Keep writing
        if (output != NULL)
        {
            fwrite(&buffer, 1, 512, output);
        }
    }
    fclose(output);
    fclose(card);
}
