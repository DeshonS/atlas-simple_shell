#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int run_cmd(char *cmd, char *flags[])
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }
    else if (pid == 0)
    {
        char *args[10];
        char *env[] = {"PATH=/bin", NULL};
        int i = 0;

        if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "pwd") == 0 || strcmp(cmd, "date") == 0)
        {
            args[i++] = cmd;
            while (flags && *flags)
            {
                args[i++] = *flags++;
            }
            args[i] = NULL;
        }
        else
        {
            fprintf(stderr, "Unknown command: %s\n", cmd);
            exit(EXIT_FAILURE);
        }

        if (execve(args[0], args, env) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            printf("Child exited with status %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child did not exit successfully\n");
        }
    }

    return 0;
}

int main()
{
    char *cmd = NULL;
    char *input = NULL;
    size_t len = 0;
    ssize_t nread;
    char *flags[10];
    int i = 0;
    char *token = strtok(input, " ");

    printf("Enter a command and flags: ");
    nread = getline(&input, &len, stdin);
    if (nread == -1)
    {
        perror("getline");
        free(input);
        return 1;
    }

    input[strcspn(input, "\n")] = 0;

    cmd = strdup(token);

    while ((token = strtok(NULL, " ")) != NULL)
    {
        flags[i++] = token;
    }
    flags[i] = NULL;

    run_cmd(cmd, flags);

    free(cmd);
    free(input);
    return 0;
}