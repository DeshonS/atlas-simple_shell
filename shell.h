#infdef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unisted.h>

int main (void);
void tokenize_input(cahr *input, char **args);
void get_command(char **input);
int is_background(char *args);