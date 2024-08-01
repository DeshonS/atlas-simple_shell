#include "main.h"

char **tokenize_input(char *line)
{
    static char *tokens[100];
    char *token;
    size_t i;
    
    token = strtok(line, " ");
    for(i = 0; token != NULL && i < 100; i++)
    {
        tokens[i] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
    return (tokens);
}
