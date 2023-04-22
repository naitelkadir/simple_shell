#include "main.h"

/**
 * handle_eof - ...
 * @read: ...
 * @b: ... 
 *
 * Return: nothing
 */
void handle_eof(int read, char *b)
{
	(void)b;
	if (read == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(b);
		}
		exit(0);
	}
}

/**
 * check_term - ...
 * 
 * Return: ...
 */

void check_term(void)
{
	if (isatty(STDIN_FILENO))
	{
		_puts("$ ");
	}
}
		
/**
 * main - main function
 *
 * Return: always return 0
 */
int main(void)
{
	char *line = NULL;
	char **args;
	char *value, *pathname;
	size_t len = 0;
	ssize_t read = 0;
	list_t *head = '\0';
	/*void (*func)(char **);*/

	while (read != EOF)
	{
		check_term();
		read = getline(&line, &len, stdin);
		handle_eof(read, line);
		args = split_line(line, " \n");
		if (!args || !args[0])
		{
			execute_command(args);
		}
		else
		{
			value = _get_global_value("PATH");
			head = link_t(value);
			pathname = _which_file(args[0], head);
			/*func = check(args);
			if (func)
			{
				free(line);
				func(args);
			}*/
			if (!pathname)
			{
				execute_command(args);
			}
			else if (pathname)
			{
				free(args[0]);
				args[0] = pathname;
				execute_command(args);
			}
		}
	}
	free_list(head);
	free_args(args);
	free(line);
	return (0);
}
