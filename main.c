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

int main(void)
{
if (isatty(STDIN_FILENO) == 1)
{
int status = 1;
while (status == 1)
{
char *line;
char **tokens;
line = read_input();
tokens = tokenize_input(line);
if (strcmp(line, "env"))
{
    print_env();
    free(line);
    return (1);
}
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
