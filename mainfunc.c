#include "main.h"

/**
 * split_line - ...
 * @line: ...
 * @delim: ...
 * Return: ...
*/
/*
char **split_line(char *line, const char *delim)
{
	unsigned int len = 1064;
	unsigned int newsize;
	unsigned int n = 0;
	char *token;
	char **tokens = malloc(len * sizeof(char *));

	if (!tokens)
	{
		perror(_get_global_value("_"));
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[n] = str_dup(token);
		n++;
		if (n >= len)
		{
			len = len + BUFSIZE;
			newsize = len;
			tokens = _realloc(tokens, len * sizeof(char *), newsize * sizeof(char *));
		}
		token = strtok(NULL, delim);
	}
	tokens[n] = token;
	return (tokens);
	free(tokens);
}


**
 * _realloc - ...
 * @ptr: ...
 * @old_size: ...
 * @new_size: ...
 * Return: ...
 */
/*
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *res;
	unsigned int i;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
	{
		res = malloc(new_size);
		if (res == NULL)
		{
			return (NULL);
		}
		return (res);
	}
	res = malloc(new_size);
	if (res == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < old_size && i < new_size; i++)
	{
		res[i] = ((char *)ptr)[i];
	}
	free(ptr);
	return (res);
}*/
/**
 * splitstring - splits a string and makes it an array of pointers to words
 * @str: the string to be split
 * @delim: the delimiter
 * Return: array of pointers to words
 */

char **split_line(char *line, const char *delim)
{
	int i, wn;
	char **array;
	char *token;
	char *copy;

	copy = malloc(_strlen(line) + 1);
	if (copy == NULL)
	{
		perror(_get_global_value("_"));
		return (NULL);
	}
	i = 0;
	while (line[i])
	{
		copy[i] = line[i];
		i++;
	}
	copy[i] = '\0';

	token = strtok(copy, delim);
	array = malloc((sizeof(char *) * 2));
	array[0] = str_dup(token);

	i = 1;
	wn = 3;
	while (token)
	{
		token = strtok(NULL, delim);
		array = _realloc(array, (sizeof(char *) * (wn - 1)), (sizeof(char *) * wn));
		array[i] = str_dup(token);
		i++;
		wn++;
	}
	free(copy);
	return (array);
}
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *old;

	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);
	old = ptr;
	if (new == NULL)
		return (NULL);

	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			new[i] = old[i];
		free(ptr);
		for (i = old_size; i < new_size; i++)
			new[i] = '\0';
	}
	if (new_size < old_size)
	{
		for (i = 0; i < new_size; i++)
			new[i] = old[i];
		free(ptr);
	}
	return (new);
}

/**
 * execute_command - ...
 * @args: array of arguments
 *
 * Return: void
 */

void execute_command(char **args)
{
	pid_t pid;
	int status;
	int val;

	if (!args || !args[0])
	{
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(_get_global_value("_"));
	}
	if (pid == 0)
	{
		val = execve(args[0], args, environ);
		if ( val == -1)
		{
			_puts(concate_strings(_get_global_value("_"), ": 1:", args[0]));
			_puts(" not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			errno = 128 + WTERMSIG(status);
	}
}

/**
 * free_args - ...
 * @args: ...
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
}
