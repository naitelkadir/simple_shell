#include "main.h"

/**
 * split_line - ...
 * @line: ...
 *
 * Return: ...
*/

char **split_line(char *line, const char *delim)
{
        unsigned int len = 1064;
        unsigned int newsize;
        unsigned int n = 0;
	char *token;
        char **tokens = malloc(len * sizeof(char*));
        
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
                        tokens = _realloc(tokens, len * sizeof(char*), newsize * sizeof(char*));

                }
                token = strtok(NULL, delim);
        }
        tokens[n] = token;
     	return (tokens);
}


/**
 * _realloc - ...
 * @ptr: ...
 * @old_size: ...
 * @new_size: ...
 */
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
	return(res);
}
	

/**
 * execute_command - ...
 * @args: array of arguments
 *
 * Return: void
 */
void execute_command(char **args)
{
	int pid;
	int status;
	
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
		execve(args[0], args, environ);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
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
