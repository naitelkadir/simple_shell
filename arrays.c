#include "main.h"

/**
 * _strlen - ...
 * @str: ...
 * 
 * Return: ...
 */
int _strlen(char *str)
{
	int c = 0;
	while (str[c] != '\0')
	{
		c++;
	}
	return (c);
}

/*-------------------------------------------------*/
/**
 * str_dup - ...
 * @s1: ...
 *
 * Return: ...
 */
char *str_dup(char *s1)
{
	int i = 0;
	int j;
	char *s2;
	
	if (s1 == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		i++;
	}
	s2 = malloc(sizeof(char) * i + 1);
	if (s2 == NULL)
	{
		return (NULL);
	}
	for (j = 0; j < i; j++)
	{
		s2[j] = s1[j];
	}
	s2[i] = s1[i];
	return (s2);
}

/*------------------------------------------------------*/
/**
 * concate_strings - ...
 * @s1: ...
 * @s2: ...
 * @s3: ...
 *
 * Return: ...
 */
char *concate_strings(char *s1, char *s2, char *s3)
{
	char *res;
	int len1, len2, len3, m, i;
	len1 = _strlen(s1);
	len2 = _strlen(s2);
	len3 = _strlen(s3);

	res = malloc(len1 + len2 + len3 + 1);
	if (res == NULL)
	{
		return (NULL);
	}
	for (i = 0; s1[i] != '\0'; i++)
	{
		res[i] = s1[i];
	}
	m = i;
	for (i = 0; s2[i] != '\0'; i++)
	{
		res[m + i] = s2[i];
	}
	m = m + i;
	for (i = 0; s3[i] != '\0'; i++)
	{
		res[m + i] = s3[i];
	}
	m = m + i;
	res[m] = '\0';
	return (res);
}

/*-----------------------------------------------------*/

/**
 *_putchar - write the character c to stdout
 * @c: the caracter to print 
 *
 * Return: 1 on success and -1 on error
 */
int _putchar(char c)
{
	return(write(1, &c, 1));
}

/*-------------------------------------------------------*/

/**
 *_puts - ...
 * @s: ...
 *
 */
void _puts(char *s)
{
	int i = 0;
	
	while(s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}
/*------------------------------------------------------------*/
	
char *_strcpy(char *dest, const char *src)
{
	int i;
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}	
