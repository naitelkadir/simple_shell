#include "main.h"


/**
 * str_len - ...
 * @s: ...
 * Return: ...
 */
int str_len(char *s)
{
	int c = 0;

	if (s == NULL)
	{	
		return (0);
	}
	while (s[c] != '\0')
	{
		c++;
	}
	return (c);
}

/**
 * str_dup - ...
 * @s: ...
 * Return: ...
 */
char *str_dup(char *s)
{
	char *res;
	int i, c;
	
	if (s == NULL)
	{
		return (NULL);
	}
	c = str_len(s) + 1;
	res = malloc (sizeof(char) * c);
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < c; i++)
	{
		res[i] = s[i];
	}
	return (res);
}

/**
 * str_cmp - ...
 * @s1: ...
 * @s2: ...
 * n: ...
 *Return: ...
 */
int str_cmp(char *s1, char *s2, int n)
{
	int i;
	
	if (s1 == NULL && s2 == NULL)
	{
		return (1);
	}
	if (s1 == NULL || s2 == NULL)
	{
		return (0);
	}
	if (n == 0)
	{
		if (str_len(s1) != str_len(s2))
		{
			return (0);
		}
		for (i = 0; s1[i]; i++)
		{
			if (s1[i] != s2[i])
			{
				return (0);
			}
		}
		return (1);
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			if (s1[i] != s2[i])
			return (0);
			
		}
		return (1);
	}
}

/**
 * concate_string - ...
 * @s1: ...
 * @s2: ...
 * Return: ...
 */
char *concate_string(char *s1, char *s2)
{
	char *res;
	int len1 = 0;
	int len2 = 0;
	
	if (s1 == NULL)
	{
		s1 = "";
	}
	len1 = str_len(s1);
	if (s2 == NULL)
	{
		s2 = "";
	}
	len2 = str_len(s2);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; s1[len1] != '\0'; len1++)
	{
		res[len1] = s1[len1];
	}
	free(s1);
	for (len2 = 0; s2[len2] != '\0'; len2++)
	{
		res[len1] = s2[len2];
		len1++;
	}
	res[len1] = '\0';
	return (res);
}

/**
 * str_reverse - ...
 * @s: ...
 * Return: ...
 */
void str_reverse(char *s)
{
	int i = 0;
	int len = str_len(s) - 1;
	char new;
	
	while (i < len)
	{
		new = s[i];
		s[i++] = s[len];
		s[len--] = new;
	}
}
