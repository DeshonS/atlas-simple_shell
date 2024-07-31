#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_CMD_LEN 100

void prompt() {
    printf("simple_shell> ");
}

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[2];
    int status;
    
    while (1) {
        prompt();

        if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL) {
            printf("\n");
            break;
        }

        cmd[strcspn(cmd, "\n")] = '\0';  // Remove the newline character

        if (strlen(cmd) == 0) {
            continue;
        }

        args[0] = cmd;
        args[1] = NULL;

        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            if (execve(cmd, args, environ) == -1) {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
        }
    }
    return 0;
}