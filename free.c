#include "main.h"

/**
 * free_command - ...
 * @cmd: ...
 * Return: ...
 */
void free_command(command_life *cmd)
{
	if (cmd->tokens)
	{
		free_array(cmd->tokens);
	}
	if (cmd->line)
	{
		free(cmd->line);
	}
	if (cmd->command_name)
	{
		free(cmd->command_name);
	}
	cmd->line = NULL;
	cmd->command_name = NULL;
	cmd->tokens = NULL;
}

/**
 * free_all - ...
 * @cmd: ...
 * Return: ..
 */
void free_all(command_life *cmd)
{
	if (cmd->fd != 0)
	{
		if (close(cmd->fd))
		{
			perror(cmd->name);
		}
	}
	free_command(cmd);
	free_array(cmd->env);
	free_array(cmd->alias_t);
}

/**
 * free_array - ...
 * @array: ...
 * Return: ...
 */
void free_array(char **array)
{
	int i;
	
	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
		{
			free(array[i]);
		}
		free(array);
		array = NULL;
	}
}
