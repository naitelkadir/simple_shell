#include "main.h"

/**
 * enver - ...
 * @cmd: ...
 * Return: ...
 */
int enver(command_life *cmd)
{
	int i;
	char cp[50] = {'\0'};
	char *copy = NULL;
	
	if (cmd->tokens[1] == NULL)
	{
		print_environ(cmd);
	}
	else
	{
		for (i = 0; cmd->tokens[1][i]; i++)
		{
			if (cmd->tokens[1][i] == '=')
			{
				copy = str_dup(get_value(cp, cmd));
				if (copy != NULL)
				{
					set_value(cp, cmd->tokens[1] + i + 1, cmd);
				}
				print_environ(cmd);
				if (get_value(cp, cmd) == NULL)
				{
					_puts(cmd->tokens[1]);
					_puts("\n");
				}
				else
				{
					set_value(cp, copy, cmd);
					free(copy);
				}
				return (0);
			}
			cp[i] = cmd->tokens[1][i];
		}
		errno = 2;
		perror(cmd->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_setenv - ...
 * @cmd: ...
 * Return: ...
 */
int builtin_setenv(command_life *cmd)
{
	if (cmd->tokens[1] == NULL || cmd->tokens[2] == NULL)
	{
		return (0);
	}
	if (cmd->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(cmd->command_name);
		return (5);
	}
	set_value(cmd->tokens[1], cmd->tokens[2], cmd);
	return (0);
}

/**
 * un_setenv - ...
 * @cmd: ...
 * Return: ...
 */
int un_setenv(command_life *cmd)
{
	if (cmd->tokens[1] == NULL)
	{
		return (0);
	}
	if (cmd->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(cmd->command_name);
		return (5);
	}
	remove_value(cmd->tokens[1], cmd);
	return (0);
}
