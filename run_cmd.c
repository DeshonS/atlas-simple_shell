#include "main.h"

typedef struct command {
    char *input;
    char *path;
} command;

void run_cmd(char **tokens)
{
    pid_t pid = fork();
    int i, fd = -1;
    char *args[100];
    char *filename = NULL;
    int j = 0;

    command commands[] = {
        {"ls", "/bin/ls"},
        {"exit", "/bin/exit"},
        {NULL, NULL} 
    };

    if (pid == -1)
    {
        perror("forking error");
        exit(1);
    }
    else if (pid == 0)
    {
        char *env[] = {"PATH=/bin", NULL};

        for (i = 0; tokens[i] != NULL; i++)
        {
            if (strcmp(tokens[i], ">") == 0)
            {
                if (tokens[i + 1] != NULL)
                {
                    filename = tokens[i + 1];
                    break;
                }
                else
                {
                    fprintf(stderr, "Syntax error: Missing filename after '>'\n");
                    exit(1);
                }
            }
            args[j++] = tokens[i];
        }
        args[j] = NULL;

        if (filename)
        {
            fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
            {
                perror("open");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2");
                close(fd);
                exit(1);
            }
            close(fd);
        }

        for (i = 0; commands[i].input != NULL; i++)
        {
            if (strcmp(commands[i].input, args[0]) == 0)
            {
                execve(commands[i].path, args, env);
                perror("execve error");
                exit(EXIT_FAILURE);
            }
        }

        perror("command not found");
        exit(-1);
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
