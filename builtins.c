#include "main.h"

/**
 *_exit: ...
 * @cmd: ...
 * Return: ...
 */
int exi_t(command_life *cmd)
{
	int i;
	
	if (cmd->tokens[1] != NULL)
	{
		for (i = 0; cmd->tokens[1][i]; i++)
		{
			if ((cmd->tokens[1][i] < '0' || cmd->tokens[1][i] > '9') && cmd->tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		}
		errno = myAtoi(cmd->tokens[1]);
	}
	free_all(cmd);
	exit(errno);
}

/**
 * _cd - ...
 * @cmd: ...
 * Return: ...
 */
int _cd(command_life *cmd)
{
	char *dir = get_value("HOME", cmd), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_c = 0;
	
	if (cmd->tokens[1])
	{
		if (str_cmp(cmd->tokens[1], "-", 0))
		{
			dir_old = get_value("OLDPWD", cmd);
			if (dir_old)
			{
				error_c = current_dir(cmd, dir_old);
			}
			_puts(get_value("PWD", cmd));
			_puts("\n");
			return (error_c);
		}
		else
		{
			return (current_dir(cmd, cmd->tokens[1]));
		}
	}
	else
	{
		if (!dir)
		{
			dir = getcwd(old_dir, 128);
		}
		return(current_dir(cmd, dir));
	}
	return (0);
}


/**
 * current_dir - ...
 * @cmd: ...
 * @str: ...
 */
int current_dir(command_life *cmd, char *str)
{
	char old_dir[128] = {0};
	int error_c;
	
	getcwd(old_dir, 128);
	if (!str_cmp(old_dir, str, 0))
	{
		error_c = chdir(str);
		if (error_c == -1)
		{
			errno = 2;
			return (3);
		}
		set_value("PWD", str, cmd);
	}
	set_value("OLDPWD", old_dir, cmd);
	return (0);
}
