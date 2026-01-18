// file.cpp
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int read_file(unsigned char **data, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        printf("Error: failed to read file: %s\n", filename);
        return -1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    *data = (unsigned char *)malloc(file_size);

    size_t bytes_read = fread(*data, 1, file_size, file);
    fclose(file);
    if (bytes_read != file_size)
    {
        printf("Error: expected to read %zu bytes. Actually read %zu\n",
               file_size, bytes_read);
        free(*data);
        *data = NULL;
        return -1;
    }

    return (int)bytes_read;
}

void print_byte(unsigned char byte)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (byte >> i) & 1;
        printf("%d", bit);
    }
    printf(" ");
    return;
}
