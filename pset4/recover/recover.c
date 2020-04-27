#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    BYTE buffer[512];
    FILE *file = fopen(argv[1], "r");
    int imageCount = 0;
    char filename[8];
    FILE *outptr = NULL;

    while (true)
    {
        size_t bytesRead = fread(buffer, sizeof(BYTE), 512, file);

        if (bytesRead == 0 && feof(file))
        {
            break;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;
        }

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outptr = fopen(filename, "w");
        }

        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }

    }

    fclose(outptr);
    fclose(file);
    return 0;
}