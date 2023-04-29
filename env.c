#include "main.h"

/**
 * get_value - ...
 * @val: ...
 * @cmd: ...
 * Return: ...
 */
char *get_value(char *val, command_life *cmd)
{
	int i, len = 0;

	if (val == NULL || cmd->env == NULL)
	{
		return (NULL);
	}
	len = str_len(val);
	for (i = 0; cmd->env[i]; i++)
	{
		if (str_cmp(val, cmd->env[i], len) && cmd->env[i][len] == '=')
		{
			return (cmd->env[i] + len + 1);
		}
	}
	return (NULL);
}

/**
 * set_value - ...
 * @var_name: ...
 * @val: ...
 * @cmd: ...
 * Return: ...
 */
int set_value(char *var_name, char *val, command_life *cmd)
{
	int i, len = 0, c = 1;
	
	if (var_name == NULL || val == NULL || cmd->env == NULL)
	{
		return (1);
	}
	len = str_len(var_name);
	for (i = 0; cmd->env[i]; i++)
	{
		if (str_cmp(var_name, cmd->env[i], len) && cmd->env[i][len] == '=')
		{
			c = 0;
			free(cmd->env[i]);
			break;
		}
	}
	cmd->env[i] = concate_string(str_dup(var_name), "=");
	cmd->env[i] = concate_string(cmd->env[i], val);
	if (c)
	{
		cmd->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * remove_value - ...
 * @val: ...
 * @cmd: ...
 * Return: ...
 */
int remove_value(char *val, command_life *cmd)
{
	int i, len = 0;
	
	if (val == NULL || cmd->env == NULL)
	{
		return (0);
	}
	len = str_len(val);
	for (i = 0; cmd->env[i]; i++)
	{
		if (str_cmp(val, cmd->env[i], len) && cmd->env[i][len] == '=')
		{
			free(cmd->env[i]);
			i++;
			for (;cmd->env[i]; i++)
			{
				cmd->env[i - 1] = cmd->env[i];
			}
			cmd->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}

/**
 * print_environ - ...
 * @cmd: ...
 * Return: ...
 */
void print_environ(command_life *cmd)
{
	int i;
	
	for (i = 0; cmd->env[i]; i++)
	{
		_puts(cmd->env[i]);
		_puts("\n");
	}
}
