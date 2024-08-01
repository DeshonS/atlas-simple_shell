#include "main.h"

typedef struct command {
    char *input;
    char *path;
} command;

void run_cmd(char *tokens)
{
    pid_t pid = fork();
    int i;
    command commands[] = {
        {"ls", "/bin/ls"},
        {"exit", "/bin/exit"},
        {"help", "/bin/help"},
        {"env", "/bin/env"},
        {NULL, NULL}
    };

    if (pid == -1)
    {
        perror("forking error");
        exit(1);
    }
    else if (pid == 0)
    {
    char *args[] = {tokens, NULL};
    char *env[] = {"PATH=/bin", NULL};
    for (i = 0; commands[i].input != NULL; i++)
    {
    if(strcmp(commands[i].input, tokens) == 0)
    {
    execve(commands[i].path, args, env);
    }
    }
    perror("command not found");
    exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if(WIFEXITED(status))
        {
            if (WEXITSTATUS(status) == 0)
            {
                printf("success\n");
            }
            else
            {
                printf("fail");
            }
        }
    }
}