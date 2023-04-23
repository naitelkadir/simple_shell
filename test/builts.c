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
				return INT_MAX;
			}
			else
			{
				return INT_MIN;
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

/**
 * env - ...
 * @args: ...
 */
void env(char **args __attribute__ ((unused)))
{
	int i;
	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}
}
			
/**
 * check - ...
 * @args: ...
 *
 * Return: ...
 */

void (*check(char **args))(char **args)
{
	int i, j;
	builtin B[] = {
		{"exit", exi_t},
		{"env", env},
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
