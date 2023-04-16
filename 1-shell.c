#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


void execute(char **args)
{
	if (args)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error :");
		}
	}
}

int main (int argc, char *args[])
{
	char *line = NULL;
	char *line_copy = NULL;
	char *delim = " \n";
	size_t len = 0;
	ssize_t read;
	int n = 0;
	char *token;
	int i;
	
	(void)argc;
	while (1)
	{
		printf("#cisfun$");
		read = getline(&line, &len, stdin);
		if (read == -1)
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
			return (-1);
		}
		line_copy = malloc(sizeof(char) * read);
		if (line_copy == NULL)
		{
			perror("lsh: memeory allocation error \n");
			return (-1);
		}
		strcpy(line_copy, line);
		token = strtok(line, delim);
		while (token != NULL)
		{
			n++;
			token = strtok(NULL, delim);
		}
		n++;
		args = malloc(sizeof(char *) * n);
		token = strtok(line_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			args[i] = malloc(sizeof(char) * strlen(token));
			strcpy(args[i], token);
			token = strtok(NULL, delim);
		}
		args[i] = NULL;
		execute(args);
	}
	free(line_copy);
	free(line);
	return (0);
}
