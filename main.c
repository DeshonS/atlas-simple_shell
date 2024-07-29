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
#define clrscr() printf("\033[1;1H\033[2J")

int main(void)
{
clrscr();
if (isatty(STDIN_FILENO) == 1)
{
shell_loop();
}
else
{
shell_ni_loop();
}
return (1);
}