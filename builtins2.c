#include "main.h"

/**
 * check_builtins - ...
 * @cmd: ...
 * Return: ...
 */
int check_builtins(command_life *cmd)
{
	int i;
	builtin_command B[] = {
		{"exit", exi_t},
		{"cd", _cd},
		{"env", enver},
		{"setenv", builtin_setenv},
		{"unsetenv", un_setenv},
		{NULL, NULL}
	};
	
	for (i = 0; B[i].builtin != NULL; i++)
	{
		if (str_cmp(B[i].builtin, cmd->command_name, 0))
		{
			return (B[i].f(cmd));
		}
	}
	return (-1);
}
