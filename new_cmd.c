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
#include <sys/wait.h>
#include "main.h"

int new_cmd(char **request)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(request[0], request) == NULL)
        {
            perror("Error: child process");
        }
        return (-1);
    }
    else if (pid < 0)
    {
        perror("error: forking");
    }
    else
    {
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
        {
            waitpid(pid, &status, WUNTRACED);
        }
    }
    return (-1);
}