#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

char **tokenize_input(char *line)
{
    int buffer = 64;
    int i = 0;
    char **token = malloc(buffer * sizeof(char *));
    char *t;

    if (token == NULL)
    {
        fprintf(stderr, "Error");
        exit(-1);
    }
    t = strtok(line, " ");
    while (t != NULL)
    {
        if (t[0] == '#')
        {
            break;
        }
        token[i] = t;
        i++;
        if (i > buffer)
        {
            buffer = buffer + buffer;
            token = realloc(token, buffer * sizeof(char *));
            if (token == NULL)
            {
                fprintf(stderr, "error");
                exit(-1);
            }
        }
        t = strtok(NULL, " ");
    }
    token[i] = NULL;
    return (token);
}