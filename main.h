#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

/**
 * struct command - ...
 * @name: ...
 * @line: ...
 * @command_name: ...
 * @count: ...
 * @fd: ...
 * @tokens: ...
 * @env: ..
 */
typedef struct command
{
	char *name;
	char *line;
	char *command_name;
	int count;
	int fd;
	char **tokens;
	char **env;
	char **alias_t;
} command_life;

#define MSG "$ "
#define BUFFER_SIZE 1024

/**
 * struct builtin_command - ...
 * @name: ...
 * @f: ...
 */
typedef struct builtin_command
{
	char *builtin;
	int (*f)(command_life *cmd);
}builtin_command;

int str_len(char *s);
char *str_dup(char *s);
int str_cmp(char *s1, char *s2, int n);
char *concate_string(char *s1, char *s2);
void str_reverse(char *s);

int _puts(char *s);
int _printe(char *s);
int _print_error(int error_c, command_life *cmd);

void num_to_string(long num, char *s, int base);
int myAtoi(char *s);
int counter(char *s, char *caract);
int execute_command(command_life *cmd);

int get_line(command_life *cmd);
int check_ops(char *array_cmd[], int n, char array_op[]);

char *str_tok(char *line, char *delim);
void token_it(command_life *cmd);

void free_command(command_life *cmd);
void free_all(command_life *cmd);
void free_array(char **array);

char *get_value(char *val, command_life *cmd);
int set_value(char *var_name, char *val, command_life *cmd);
int remove_value(char *val, command_life *cmd);
void print_environ(command_life *cmd);

int find_p(command_life *cmd);
char **token_path(command_life *cmd);
int check_f(char *path);

int exi_t(command_life *cmd);
int _cd(command_life *cmd);
int current_dir(command_life *cmd, char *str);

int check_builtins(command_life *cmd);
int enver(command_life *cmd);
int builtin_setenv(command_life *cmd);
int un_setenv(command_life *cmd);

int main(int argc, char *argv[], char *env[]);
void initializer(command_life *cmd, int argc, char *argv[], char **env);
void handle_c(int num __attribute__ ((unused)));
void sh_loop(char *prompt, command_life *cmd);

void expand_variables(command_life *cmd);
void expand_alias(command_life *cmd);
int add_at_end(char *b, char *s);

int print_alias(command_life *data, char *alias);
char *get_alias(command_life *data, char *name);
int set_alias(char *alias_string, command_life *data);


#endif
