#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 100

int main(int argc, char *argv[])
{
    // Check for correct argument count
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // opening the image file
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // frequency array
    long byteFrequency[256] = {0};
    unsigned char byte;
    size_t bytesRead;
    long maxFrequency = 0;

    // Read the file byte by byte and count frequencies
    while ((bytesRead = fread(&byte, sizeof(byte), 1, file)) > 0)
    {
        byteFrequency[byte]++;
        if (byteFrequency[byte] > maxFrequency)
        {
            maxFrequency = byteFrequency[byte];
        }
    }

    if (ferror(file))
    {
        perror("Error reading file");
        fclose(file);
        return EXIT_FAILURE;
    }

    // Close the file
    fclose(file);

    // Normalize the frequencies to the MAX_HEIGHT
    long scaleFactor = (maxFrequency + MAX_WIDTH - 1) / MAX_WIDTH; // Ceiling division

    printf("Frequency Histogram for jpg bytes\n");
    for (int i = 0; i < 256; i++)
    {
        if (byteFrequency[i] > 0)
        {
            int height = byteFrequency[i] / scaleFactor;
            printf("0x%02X (%3d) | ", i, i);
            for (int j = 0; j < height; j++)
            {
                printf("*");
            }
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}
