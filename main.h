#ifndef MAIN_H
#define MAIN_H

void shell_loop(void);
char *read_input(void);
char **tokenize_input(char *line);
int run_cmd(char **request);
int new_cd(char **request);
int new_help(char **request);
int new_cwd(char **request);
int new_env(char **request);
int new_exit(char **request);
int new_cmd(char **request);
void shell_ni_loop(void);
int new_cd(char **request);
int new_env(char **request);
int new_exit(char **request);
int new_help(char **request);
int new_cwd(char **request);

#endif