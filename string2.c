#include "main.h"

/**
 * _puts - ...
 * @s: ...
 * Return: ...
 */
int _puts(char *s)
{
	return (write(STDOUT_FILENO, s, str_len(s)));
}
/**
 * _printe - ...
 * @s: ...
 * Return: ...
 */
int _printe(char *s)
{
	return (write(STDERR_FILENO, s, str_len(s)));
}

/**
 * _print_error - ...
 * @cmd: ...
 * @error_c: ...
 * Return: ...
 */
int _print_error(int error_c, command_life *cmd)
{
	char str[10] = {'\0'};
	
	num_to_string((long) cmd->count, str, 10);
	if (error_c == 2 || error_c == 3)
	{
		_printe(cmd->name);
		_printe(": ");
		_printe(str);
		_printe(": ");
		_printe(cmd->tokens[0]);
		if (error_c == 2)
		{
			_printe(":Illegal number: "); 
		}
		else
		{
			_printe(": can't cd to ");
		}
		_printe(cmd->tokens[1]);
		_printe("\n");
	}
	else if (error_c == 127)
	{
			_printe(cmd->name);
			_printe(": ");
			_printe(str);
			_printe(": ");
			_printe(cmd->command_name);
			_printe(": not found\n");
	}
	else if (error_c == 126)
	{
		_printe(cmd->name);
		_printe(": ");
		_printe(str);
		_printe(": ");
		_printe(cmd->command_name);
		_printe(": Permision denied\n");
	}
	return (0);
}
