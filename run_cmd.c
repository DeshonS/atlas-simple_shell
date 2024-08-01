#include "main.h"

typedef struct command {
    char *input;
    char *path;
} command;

void run_cmd(char **tokens)
{
    pid_t pid = fork();
    int i;
    command commands[] = {
        {"ls", "/bin/ls"},
        {"exit", "/bin/exit"},
    };

    if (pid == -1)
    {
        perror("forking error");
        exit(1);
    }
    else if (pid == 0)
    {
        char *env[] = {"PATH=/bin", NULL};

        printf("%s\n", tokens[0]);
        for (i = 0; commands[i].input != NULL; i++)
        {
            if (strcmp(commands[i].input, tokens[0]) == 0)
            {
                execve(commands[i].path, tokens, env);
                perror("execve error");
                exit(EXIT_FAILURE);
            }
        }

        perror("command not found");
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) != 0)
            {
                printf("Command failed with exit code %d\n", WEXITSTATUS(status));
            }
            else
            {
                printf("success\n");
            }
        }
    }
}