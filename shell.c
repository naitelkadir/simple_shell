#include "shell.h"

int main(int argc, char *argv[])
{
lsh_loop();
return EXIT_SUCCESS;
}

void lsh_loop(void)
{
char *line;
char **args;
int status;

do {
printf("> ");
line = read_line();
args = split_line(line);
status = lsh_execute(args);

free(line);
free(args);
} while (status);
}

char *read_line(void)
{
char *line = NULL;
ssize_t len = 0;

if (getline(&line, &len, stdin) == -1)
{
if (feof(stdin))
{
exit(EXIT_SUCCESS);
}
else
{
perror("readline");
exit(EXIT_FAILURE);
}
}
return (line);
}

char **split_line(char *line)
{
int bufsize = 64;
int position = 0;
char **tokens = malloc(bufsize * sizeof(char*));
char *token;

if (!tokens)
{
fprintf(stderr, "lsh: allocation error\n");
exit(EXIT_FAILURE);
}
token = strtok(line,"");
while (token != NULL)
{
tokens[position] = token;
position++;

if (position >= bufsize)
{
bufsize += 64;
tokens = realloc(tokens, bufsize * sizeof(char*));
if (!tokens)
{
fprintf(stderr, "allocation error\n");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, "");
}
tokens[position] = NULL;
return (tokens);
}

int lsh_execute(char **args)
{
pid_t pid, wpid;
int status;

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("lsh");
}
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("ls");
}
else
{
do {
wpid = waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
return (1);
}
