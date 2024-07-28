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
char *userid = getlogin();
hostname = gethostname(username, sizeof(username));
getcwd(cwd, sizeof(cwd));
checkhostname(hostname);
char *line;
char **request;
int execute = -1;
while (execute == -1)
{
printf("\033[0;32m");
printf("%s@%s", userid, username);
printf("\033[0;34m");
printf(":%s", cwd);
printf("\033[0;37m");
line = read_input(); /*script that reads the input*/
request = tokenize_input(line); /*read_input passes the return to be tokenized*/
execute = run_cmd(request); /*tokenize passes the tokens to run_cmd to execute*/
free(line); /*free memory*/
free(request); /*free memory*/
if (execute >= 0) /*if run_cmd returns anything other than -1 (or continue)*/
{
    exit(execute); /*exit process*/
}
}
}