#include "main.h"

char **tokenize_input(char *line)
{
    char **tokens;
    char *token;
    size_t i;
    
    tokens = (char **)malloc(sizeof(char) * sizeof(line));
    if (tokens == NULL)
    {
        perror("Allocation error");
        exit(1);
    }
    token = strtok(line, " ");
    for(i = 0; token != NULL && i < 100; i++)
    {
        tokens[i] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return (tokens);
}
