#include "main.h"
#include <limits.h>

/**
 * myAtoi - ...
 * @str: ...
 *
 * Return: ...
 */
int myAtoi(char *str)
{
	int sign = 1, base = 0, i = 0;

	while (str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1 - 2 * (str[i++] == '-');
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7))
		{
			if (sign == 1)
			{
				return (INT_MAX);
			}
			else
			{
				return (INT_MIN);
			}
		}
		base = 10 * base + (str[i++] - '0');
	}
	return (base * sign);
}
/**
 * exi_t - ...
 * @args: ...
 *
 * Return: void
 */
/*
void exi_t(char **args)
{
	int i, n;

	if (args[1] != 	NULL)
	{
		n = myAtoi(args[1]);
		if (n <= -1)
		{
			n = 2;
		}
		free_args(args);
		exit(n);
	}
	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
	exit(0);
}
*/

void exi_t(char ** args)
{
	int i;

	if (args[1] != NULL)
	{
		for (i = 0; args[1][i]; i++)
		{	if ((args[1][i] < '0' || args[1][i] > '9')
				&& args[1][i] != '+')
			{
				errno = 2;
			}
			free(args[i]);
		}
		errno = myAtoi(args[1]);
	}
	free_args(args);
	exit(errno);
}

/**
 * enver - ...
 * @args: ...
 */
void enver(char **args __attribute__ ((unused)))
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}

/**
 * changeDir - ...
 * @args: ...
 *
 *Return: nothing
 */
/**
 * set_env - ...
 * @args: ...
 * Return: ...
 */
void set_env(char **args)
{
	int i, j, l;

	if (!args[1] || !args[2])
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
				l = 0;
				while (args[2][l])
				{
					environ[i][j + 1 + l] = args[2][l];
					l++;
				}
				environ[i][j + 1 + l] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{
		environ[i] = concate_strings(args[1], "=", args[2]);
		environ[i + 1] = '\0';
	}
}
