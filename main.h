#ifndef MAIN_H
#define MAIN_H

void shell_loop(void);
char *read_input(void);
char **tokenize_input(char *line);
int run_cmd(char **request);

#endif