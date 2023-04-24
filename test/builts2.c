#include "main.h"

/**
 * un_setenv - ...
 * @args: ...
 *
 * Return: nothing
 */
void un_setenv(char **args)
{
	int i, j;

	if (!args[1])
	{
		perror(_get_global_value("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (args[1][j] == environ[i][j])
		{
			while (args[1][j])
			{
				if (args[1][j] != environ[i][j])
				{
					break;
				}
				j++;
			}
			if (args[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}

void (*check(char **args))(char **args)
{
	int i, j;
	builtin B[] = {
		{"exit", exi_t},
		{"env", env},
		{"cd", changeDir},
		{"setenv", set_env},
		{"unsetenv", un_setenv},
		{NULL, NULL}
	};
	for (i = 0; B[i].name; i++)
	{
		j = 0;
		if (B[i].name[j] == args[0][j])
		{
			for (j = 0; args[0][j]; j++)
			{
				if (B[i].name[j] != args[0][j])
				{
					break;
				}
			}
			if (!args[0][j])
			{
				return (B[i].f);
			}
		}
	}
	return (0);
}

