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

char *read_input(void)
{
    char *line = NULL; /*needed to init variables to prevent errors*/
    long unsigned int buffer = 0;

    if(getline(&line, &buffer, stdin) == -1) /*if getline has an error*/
    {
        if(feof(stdin)) /*if we have reached end of file*/
        {
            free(line); /*free the memory*/
            exit(1); /*exit success*/
        }
        else
        {
            free(line); /*free memory*/
            perror("Error reading input"); /*error message*/
            exit(-1); /*exit failure*/
        }
    }
    return(line); /*return input*/
}