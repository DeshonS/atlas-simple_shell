#include "main.h"

void checkhostname(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

char *read_input(void)
{
    char *buffer;
    size_t size = 32;
    char *line = NULL;
    char hostname;
    char username[1024];
    char cwd[64];
    char *userid = getlogin();
    hostname = gethostname(username, sizeof(username));
    getcwd(cwd, sizeof(cwd));
    checkhostname(hostname);

    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL)
    {
        perror("Allocation error in read_input");
        free(buffer);
        exit(1);
    }
    printf("\033[0;32m");
    printf("%s@%s", userid, username);
    printf("\033[0;34m");
    printf(":%s", cwd);
    printf("\033[0;37m");
    getline(&line, &size, stdin);
    if (line == NULL)
    {
        perror("Read error in read_input");
        free(buffer);
        exit(1);
    }
    line[strcspn(line, "\n")] = 0;
    free(buffer);
    return (line);
}