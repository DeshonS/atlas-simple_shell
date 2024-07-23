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

#define clrscr() printf("\e[1;1H\e[2J")

void checkhostname(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

void shell_loop(void)
{
char hostname;
char username[1024];
char cwd[64];
char input[128];
hostname = gethostname(username, sizeof(username));
getcwd(cwd, sizeof(cwd));
checkhostname(hostname);
char *line;
char **args;
for (;;)
{
printf("\033[0;32m");
printf("%s", username);
printf("\033[0;34m");
printf(":%s", cwd);
printf("\033[0;37m");
fputs("$ ", stdout);
fflush(stdout);
fgets(input, sizeof(input), stdin);
if (input == "exit")
{
    break;
}
system(input);
}
}