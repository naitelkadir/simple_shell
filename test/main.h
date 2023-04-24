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

int _strlen(char *str);
char *str_dup(char *s1);
char *concate_strings(char *s1, char *s2, char *s3);
char *_strcpy(char *dest, const char *src);
int _putchar(char c);
void _puts(char *s);
int read_line(char *line);

/**
 * struct list_t - linked list
 * @dir: ...
 * @p: ...
 */
typedef struct list_t
{
	char *dir;
	struct list_t *p;
}list_t;

/**
 * struct built_func - ...
 * @name: ...
 * @f: ...
 */
typedef struct builtin
{
	char *name;
	void (*f)(char **);
}builtin;

#define BUFSIZE 1024
extern char **environ;

char *_get_global_value(const char *str);
list_t *add_node_end(list_t **head, char *str);
list_t *link_t(char *path);
char *_which_file(char *filename, list_t *head);
void free_list(list_t *head);
int myAtoi(char *str);
void exi_t(char **args);
void execute_command(char **args);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **split_line(char *line, const char *delim);
void env(char **args __attribute__ ((unused)));
void (*check(char **args))(char **args);
void free_args(char **args);
void handle_eof(int read, char *b);
void set_env(char **args);
void un_setenv(char **args);
void changeDir(char **args);
void check_term(void);

#endif
