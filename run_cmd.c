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

int **run_cmd(char *token)
{
    char args[] = {token[0], token[1], token[2], NULL};
    pid_t pid;
    int status;
    char *env_args[] = {"PATH=/bin", (char*)0};

    pid = fork();
    if (pid == 0)
    {
    if (execve(token[0], args[], env_args[]) == -1)
    {
        perror("Error in child process");
    }
    exit(-1);
    else if (pid < 0)
    {
        perror("forking error");
    }
    else
    {
        while (!WIFEXITED(status) && !WIFSIGNALED(status))
        {
            waitpid(pid, &status, WUNTRACED);
        }
    }
    }
    return (-1);
}