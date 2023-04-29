#include "main.h"

/**
 * str_tok - ...
 * @line: ...
 * @delim: ...
 *
 * Return: ...
 */
char *str_tok(char *line, char *delim)
{
	int i;
	static char *s;
	char *copy;
	
	if (line != NULL)
	{
		s = line;
	}
	for (; *s != '\0'; s++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*s == delim[i])
			break;
		}
		if (delim[i] == '\0')
		{
			break;
		}
	}
	copy = s;
	if (*copy == '\0')
	{
		return (NULL);
	}
	for (; *s != '\0'; s++)
	{
		for (i = 0; delim[i] != '\0'; i++)
		{
			if (*s == delim[i])
			{
				*s = '\0';
				s++;
				return (copy);
			}
		}
	}
	return (copy);
}
