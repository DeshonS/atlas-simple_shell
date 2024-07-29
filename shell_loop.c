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
char *userid = getlogin();
char *line;
char **request;
int execute = -1;
line = read_input();
request = tokenize_input(line);
execute = run_cmd(request);
hostname = gethostname(username, sizeof(username));
getcwd(cwd, sizeof(cwd));
checkhostname(hostname);

while (execute == -1)
{
printf("\033[0;32m");
printf("%s@%s", userid, username);
printf("\033[0;34m");
printf(":%s", cwd);
printf("\033[0;37m");
free(line);
free(request);
if (execute >= 0)
{
    exit(execute);
}
}
}