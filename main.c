#include "main.h"

/**
 * main - ...
 * @argc: ...
 * @argv: ...
 * @env: ...
 * Return: always 0 in success
 */
int main(int argc, char *argv[], char *env[])
{
	char *prompt = "";
	command_life info_struct = {NULL};
	command_life *data = &info_struct;
	
	initializer(data, argc, argv, env);
	signal(SIGINT, handle_c);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = MSG;
	}
	errno = 0;
	sh_loop(prompt, data);
	return (0);
}

/**
 * handle_c - ...
 * @num: ...
 * Return: ...
 */
void handle_c(int num __attribute__((unused)))
{
	_puts("\n");
	_puts(MSG);
}

void initializer(command_life *cmd, int argc, char *argv[], char **env)
{
	int i = 0;
	
	cmd->name = argv[0];
	cmd->line = NULL;
	cmd->command_name = NULL;
	cmd->count = 0;
	if (argc == 1)
	{
		cmd->fd = STDIN_FILENO;
	}
	else
	{
		cmd->fd = open(argv[1], O_RDONLY);
		if (cmd->fd == -1)
		{
			_puts(cmd->name);
			_puts(": 0: can't open ");
			_puts(argv[1]);
			_puts("\n");
			exit(127);
		}
	}
	cmd->tokens = NULL;
	cmd->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			cmd->env[i] = str_dup(env[i]);
		}
	}
	cmd->env[i] = NULL;
	env = cmd->env;
	cmd->alias_t = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		cmd->alias_t = NULL;
	}
}

void sh_loop(char *prompt, command_life *cmd)
{
	int error = 0;
	int len = 0;
	
	while (++(cmd->count))
	{
		_puts(prompt);
		error = len = get_line(cmd);
		if (error == EOF)
		{
			free_all(cmd);
			exit(errno);
		}
		if (len >= 1)
		{
			expand_alias(cmd);
			expand_variables(cmd);
			token_it(cmd);
			if (cmd->tokens[0])
			{
				error = execute_command(cmd);
				if (error != 0)
				{
					_print_error(error, cmd);
				}
			}
			free_command(cmd);
		}
	}
}
