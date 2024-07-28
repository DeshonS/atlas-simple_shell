#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
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
    char **token = malloc(buffer * sizeof(char *)); /*allocate memory for tokens*/
    char *t;

    if (token == NULL) /*standard memory error handling*/
    {
        fprintf(stderr, "Error"); /*print error message*/
        exit(-1); /*exit failure*/
    }
    t = strtok(line, " "); /*tokenize input using spaces as breaks*/
    while (t != NULL)
    {
        if (t[0] == '#') /*if the line is a comment*/
        {
            break; /*ignore this line*/
        }
        token[i] = t; /*glorified strcpy*/
        i++; /*iterate through the input*/
        if (i > buffer) /*if theres not enough memory allocated*/
        {
            buffer = buffer + buffer; /*set buffer to double its size*/
            token = realloc(token, buffer * sizeof(char *)); /*reallocate memory*/
            if (token == NULL) /*same error handling for memory*/
            {
                fprintf(stderr, "error"); /*error message*/
                exit(-1); /*exit failure*/
            }
        }
        t = strtok(NULL, " "); /*tokenize input as before*/
    }
    token[i] = NULL; /*end tokenization with null to put a cap on the marker*/
    return (token); /*return tokenized command*/
}