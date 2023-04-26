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
 * Return: ...
 */

void check_term(void)
{
	if (isatty(STDIN_FILENO))
	{
		_puts("#cisfun$  ");
	}
}
/**
 * handle_c - ...
 * @num: ...
 */
void handle_c(int num)
{
	if (num == SIGINT)
	{
		_puts("\n#cisfun$  ");
	}
}
/**
 * main - main function
 * Return: always return 0
 */
int main(void)
{	char *line = NULL, *value, *path_name, **args;
	size_t len = 0;
	ssize_t read = 0;
	list_t *head = '\0';
	void (*func)(char **);

	signal(SIGINT, handle_c);
	while (read != -1)
	{
		check_term();
		read = getline(&line, &len, stdin);
		handle_eof(read, line);
		args = split_line(line, " \t\r\n\a");
		if (!args || !args[0])
		{	execute_command(args);
		}
		else
		{	value = _get_global_value("PATH");
			head = add_all(value);
			path_name = _which_file(args[0], head);
			func = checkInternal(args);
			if (func)
			{	free(line);
				func(args);
			}
			else if (!path_name)
			{
				execute_command(args);
			}
			else if (path_name)
			{
				free(args[0]);
				args[0] = path_name;
				execute_command(args);
			}
		}
	}
	free_list(head);
	free_args(args);
	free(line);
	return (0);
}
