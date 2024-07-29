#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"

int run_cmd(char **request)
{
    char *builtin[] = {
        "cd",
        "help",
        "cwd",
        "exit",
        "env"
    };
    int (*builtin_cmd[])(char **) = {
        &new_cd,
        &new_help,
        &new_cwd,
        &new_exit,
        &new_env,
    };
    long unsigned int i;

    if(request[0] == NULL)
    {
        return (-1);
    }
    for (i = 0; i < sizeof(builtin) / sizeof(char *); i++)
    {
        if (strcmp(request[0], builtin[i]) == 0)
        {
            return ((*builtin_cmd[i])(request));
        }
    }
    return (new_cmd(request));
}