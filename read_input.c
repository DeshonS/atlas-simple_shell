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
    char *line = NULL;
    long unsigned int buffer = 0;

    if(getline(&line, &buffer, stdin) == -1)
    {
        if(feof(stdin))
        {
            free(line);
            exit(1);
        }
        else
        {
            free(line);
            perror("Error reading input");
            exit(-1);
        }
    }
    return(line);
}