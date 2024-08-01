#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "main.h"
#define clrscr() printf("\033[1;1H\033[2J")

int main(void)
{
clrscr();
if (isatty(STDIN_FILENO) == 1)
{
int status = 1;
while (status == 1)
{
char *line = read_input();
if (line == "exit")
{
    exit(1);
}
if (line == "env")
{
    print_env();
    free(line);
    return (1);
}
char **tokens = tokenize_input(line);
run_cmd(tokens);
free(line);
free(tokens);
}
}
/*else
{
shell_ni_loop();
}*/
return (0);
}