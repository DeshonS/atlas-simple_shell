#include "main.h"

char *read_input(void)
{
    char *buffer;
    size_t size = 32;
    char *line = NULL;

    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL)
    {
        perror("Allocation error in read_input");
        free(buffer);
        exit(1);
    }
    printf("S");
    getline(&line, &size, stdin);
    if (line == NULL)
    {
        perror("Read error in read_input");
        free(buffer);
        exit(1);
    }
    line[strcspn(line, "\n")] = 0;
    free(buffer);
    return (line);
}